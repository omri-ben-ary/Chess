//questions:
//  1. gal's notepad
//
//
//
//
//
//
//
//

#include <stdlib.h>
#include "chessSystem.h"
#include "players_map.h"
#include "assert.h"
#include "tournament.h"
#include <string.h>
#include <stdbool.h>
// OMRI should add his header files here

#define ERROR_CODE (-1)
#define WIN 0
#define TIE 2
#define LOSE 1
#define REMOVE_PLAYER_ID 1
#define CALCULATE_AVERAGE_PLAY_TIME 2
#define POINTS_PER_WIN 6
#define POINTS_PER_TIE (-10)
#define POINTS_PER_LOSE 2
#define SIZE_OF_PAIR 2
#define FIRST_CAPITAL_LETTER 'A'
#define LAST_CAPITAL_LETTER 'Z'
#define FIRST_SMALL_LETTER 'a'
#define LAST_SMALL_LETTER 'z'
#define SPACE_CHAR ' '
// OMRI should add his defines here

struct chess_system_t{
    Players players;
    TournamentTable tournament_table;
    bool tournament_ended;
    // OMRI should add Tournaments here
};

// STATIC FUNCTION PROTOTYPING:
// static functions for #chessCalculateAveragePlayTime & #chessRemovePlayerParametersCheck:
static bool chessContainPlayer(ChessSystem chess, int player_id);
static ChessResult chessCalculateAveragePlayTimeOrRemovePlayerParametersCheck(ChessSystem chess, int player_id);
static double chessCalculateAveragePlayTimeOrRemovePlayer(ChessSystem chess, int player_id, ChessResult* chess_result,
                                                          int chosen_function);

// static functions for #chessSavePlayerLevels:
static ChessResult chessSavePlayersLevelsParametersCheck(ChessSystem chess, FILE* file);
static ChessResult chessUpdatePlayerStats(ChessSystem chess);
static void chessUpdatePlayerWithGameResult(Players players, PlayerID player_id, int game_result);
static int chessCalculatePlayerLevel(Players players, PlayerID player_id, int n);
static void swap(double* x, double* y);
static int bubble(double a[], int n);
static void bubble_sort(double a[], int n);
static double* chessCalculateAndSortRankings(Players players, int n);
static ChessResult chessPrintRankingsToFile(double a[], int n, FILE* file);
static ChessResult chessAddTournamentParametersCheck(ChessSystem chess, int tournament_id,
                                                     int max_games_per_player, const char* tournament_location);
static bool chessLocationNameCheck(const char* name);
static ChessResult chessAddGameParametersCheck(ChessSystem chess, int tournament_id, int first_player,
                                               int second_player, Winner winner, int play_time, int game_id);
static ChessResult chessRemoveTournamentParametersCheck(ChessSystem chess, int tournament_id);
static ChessResult chessEndTournamentParametersCheck(ChessSystem chess, int tournament_id);

// FUNCTIONS IMPLEMENTATION (STATIC FUNCTIONS (HELPERS) BEFORE THE FUNCTION THEY RELATE TO):

ChessSystem chessCreate()
{
    ChessSystem chess = malloc(sizeof(*chess));
    if (chess == NULL)
    {
        return NULL;
    }
    chess->players = playersMapCreate();
    if (chess->players == NULL)
    {
        free(chess);
        return NULL;
    }
    chess->tournament_table = tournamentTableCreate();
    if (chess->tournament_table == NULL)
    {
        playersMapDestroy(chess->players);
        free(chess);
        return NULL;
    }
    chess->tournament_ended = false;
    return chess;
}

void chessDestroy(ChessSystem chess)
{
    if(chess == NULL)
    {
        return;
    }
    playersMapDestroy(chess->players);
    tournamentTableDestroy(chess->tournament_table);
    free(chess);
}

static bool chessLocationNameCheck(const char* name)
{
    if(strlen(name) == 0)
    {
        return false;
    }

    if(*name < FIRST_CAPITAL_LETTER || *name > LAST_CAPITAL_LETTER)
    {
        return false;
    }
    while(*(++name))
    {
        if(*name < FIRST_SMALL_LETTER || *name > LAST_SMALL_LETTER)
        {
            if(*name != SPACE_CHAR)
            {
                return false;
            }
        }
    }

    return true;
}

static ChessResult chessAddTournamentParametersCheck(ChessSystem chess, int tournament_id,
                                                     int max_games_per_player, const char* tournament_location)
{
    if(chess == NULL || tournament_location == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if(tournament_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if(tournamentTableContains(chess->tournament_table, tournament_id))
    {
        return CHESS_TOURNAMENT_ALREADY_EXISTS;
    }
    if(chessLocationNameCheck(tournament_location) == false)
    {
        return CHESS_INVALID_LOCATION;
    }
    if(max_games_per_player <= 0)
    {
        return CHESS_INVALID_MAX_GAMES;
    }
    return CHESS_SUCCESS;
}

ChessResult chessAddTournament (ChessSystem chess, int tournament_id,
                                int max_games_per_player, const char* tournament_location)
{
    ChessResult parameter_check_result = chessAddTournamentParametersCheck(chess, tournament_id,
                                                                           max_games_per_player, tournament_location);
    if(parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentData tournament_data = tournamentDataCreate(tournament_location, max_games_per_player);
    TournamentError check_result = tournamentTableAddOrEditTournament(chess->tournament_table, tournament_id,
                                                                tournament_data);
    tournamentDataDestroy(tournament_data);
    if(check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    assert(check_result != TOURNAMENT_NULL_ARGUMENT);
    return CHESS_SUCCESS;
}

static ChessResult chessAddGameParametersCheck(ChessSystem chess, int tournament_id, int first_player,
                                               int second_player, Winner winner, int play_time, int game_id)
{
    if(chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if(tournament_id <= 0 || first_player <= 0 || second_player <= 0 || first_player == second_player)
    {
        return CHESS_INVALID_ID;
    }
    if(winner != FIRST_PLAYER && winner != SECOND_PLAYER && winner != DRAW)
    {
        return CHESS_INVALID_ID;
    }
    if(tournamentTableContains(chess->tournament_table, tournament_id) == false)
    {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    if(tournamentDataGetWinnerId(tournament_data) != 0)
    {
        return CHESS_TOURNAMENT_ENDED;
    }
    if(gameTableCheckIfPlayersMetAlready(game_table, first_player, second_player))
    {
        return CHESS_GAME_ALREADY_EXISTS;
    }
    if(play_time < 0)
    {
        return CHESS_INVALID_PLAY_TIME;
    }
    int max_games = tournamentDataGetMaxGames(tournament_data);
    /*if(playersMapAddGameStats(chess->players, first_player, tournament_id, game_id) == TOURNAMENT_STATS_FULL_OF_GAMES)
    {
        return CHESS_EXCEEDED_GAMES;
    }*/ // Gal to update
    return CHESS_SUCCESS;
}

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time)
{
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    int game_id = tournamentDataGetGameIndex(tournament_data);
    ChessResult parameter_check_result = chessAddGameParametersCheck(chess, tournament_id, first_player, second_player,
                                                                     winner, play_time, game_id);
    if(parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    GameResult game_result;
    if(winner == FIRST_PLAYER)
    {
        game_result = FIRST;
    }
    else if(winner == SECOND_PLAYER)
    {
        game_result = SECOND;
    } else{
        game_result = GAME_DRAW;
    }
    TournamentError  check_result = tournamentTableAddGame(chess->tournament_table, tournament_id, first_player,
                                                               second_player,game_result,play_time);
    if(check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    assert(check_result != TOURNAMENT_NULL_ARGUMENT);
    return CHESS_SUCCESS;
}

static ChessResult chessRemoveTournamentParametersCheck(ChessSystem chess, int tournament_id)
{
    if(chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if(tournament_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if(tournamentTableContains(chess->tournament_table, tournament_id) == false)
    {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    return CHESS_SUCCESS;
}

ChessResult chessRemoveTournament (ChessSystem chess, int tournament_id)
{
    ChessResult parameter_check_result = chessRemoveTournamentParametersCheck(chess, tournament_id);
    if(parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    MAP_FOREACH(int*, iterator, game_table)
    {
        GameData game_data = gameTableGetGameData(game_table, *iterator);
        int player = gameDataGetPlayer(game_data, PLAYER1);
        //Gal updates his ADT using tournament_id and player
        player = gameDataGetPlayer(game_data, PLAYER2);
        //Gal updates his ADT using tournament_id and player
        free(iterator);
    }
    TournamentError check_result = tournamentTableDeleteTournament(chess->tournament_table, tournament_id);
    assert(check_result != TOURNAMENT_NULL_ARGUMENT);
    assert(check_result != TOURNAMENT_DOES_NOT_EXIST);
    return CHESS_SUCCESS;
}

static bool chessContainPlayer(ChessSystem chess, int player_id)
{
    return (playersMapContain(chess->players, player_id));
}

static ChessResult chessCalculateAveragePlayTimeOrRemovePlayerParametersCheck(ChessSystem chess, int player_id)
{
    if (chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (player_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if (!(chessContainPlayer(chess, player_id)))
    {
        return CHESS_PLAYER_NOT_EXIST;
    }
    return CHESS_SUCCESS;
}

static double chessCalculateAveragePlayTimeOrRemovePlayer(ChessSystem chess, int player_id, ChessResult* chess_result,
                                                          int chosen_function)
{
    ChessResult parameters_check_result = chessCalculateAveragePlayTimeOrRemovePlayerParametersCheck(chess, player_id);
    if (parameters_check_result != CHESS_SUCCESS)
    {
        *chess_result = parameters_check_result;
        return ERROR_CODE; // which double should we return in case of error code?
    }
    *chess_result = CHESS_OUT_OF_MEMORY; // we assume that if the function won't get to it's end it's a memory issue
    int* player_tournaments = playersMapGetTournaments(chess->players, player_id);
    if (player_tournaments == NULL)
    {
        // should think what to return NULL POINTER/ MEMORY FAIL or something else;
        // because it's possible that the chess is not null but one of the players inside it points to null by purpose.
        // in case it's a CHESS_OUT_OF_MEMORY we need to terminate the program.
        return ERROR_CODE;
    }
    int num_of_player_tournaments = 0, k = 0;
    while (player_tournaments[k++])
    {
        num_of_player_tournaments++;
    }
    double total_play_time = 0;
    int number_of_games_for_average_game_time = 0;
    for (int i = 0; i < num_of_player_tournaments; i++)
    {
        int *player_games = playersMapGetGamesInTournament(chess->players, player_id, player_tournaments[i]);
        if (player_games == NULL)
        {
            // should think what to return NULL POINTER/ MEMORY FAIL or something else;
            // because it's possible that the chess is not null but one of the players inside it points to null by purpose.
            // in case it's a CHESS_OUT_OF_MEMORY we need to terminate the program.
            free(player_tournaments);
            return ERROR_CODE;
        }
        int num_of_games = playersMapGetMaxGamesForTournament(chess->players, player_id, player_tournaments[i]);
        if (num_of_games == ERROR_CODE)
        {
            free(player_tournaments);
            free(player_games);
            return ERROR_CODE;
        }
        for (int j = 0; j < num_of_games; j++)
        {
            if (player_games[j] == 0)
            {
                break;
            }
           if (chosen_function == REMOVE_PLAYER_ID)
           {
               TournamentError result = tournamentTableRemovePlayerInGame(chess->tournament_table, player_tournaments[i],
                                                             player_games[j], player_id);
               assert(result == TOURNAMENT_SUCCESS);
           }
           if (chosen_function == CALCULATE_AVERAGE_PLAY_TIME)
           {
               number_of_games_for_average_game_time++;
               total_play_time += tournamentTableGetGameTime(chess->tournament_table,player_tournaments[i],
                                                             player_games[j]);
           }
        }
        free(player_games);
    }
    free(player_tournaments);
    *chess_result = CHESS_SUCCESS;
    return (total_play_time/number_of_games_for_average_game_time);
}

ChessResult chessRemovePlayer(ChessSystem chess, int player_id)
{
    ChessResult chess_result; // don't sure about that line, should i malloc it?
    chessCalculateAveragePlayTimeOrRemovePlayer(chess, player_id, &chess_result, CALCULATE_AVERAGE_PLAY_TIME);
    if (chess_result == CHESS_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    if (chess_result == CHESS_SUCCESS)
    {
        playersMapRemove(chess->players, player_id);
    }
    return chess_result;
}

static ChessResult chessEndTournamentParametersCheck(ChessSystem chess, int tournament_id)
{
    if(chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if(tournament_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if(tournamentTableContains(chess->tournament_table, tournament_id) == false)
    {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    if(chess->tournament_ended == true)
    {
        return CHESS_TOURNAMENT_ENDED;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    if(gameTableGetSize(game_table) == 0)
    {
        return CHESS_NO_GAMES;
    }
    return CHESS_SUCCESS;
}

ChessResult chessEndTournament (ChessSystem chess, int tournament_id)
{
    ChessResult parameter_check_result = chessEndTournamentParametersCheck(chess, tournament_id);
    if(parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentError check_result = tournamentTableEndTournament(chess->tournament_table,tournament_id);
    if(check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    chess->tournament_ended = true;
    return CHESS_SUCCESS;
}

double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result)
{
    double result = chessCalculateAveragePlayTimeOrRemovePlayer(chess, player_id, chess_result, REMOVE_PLAYER_ID);
    if (*chess_result == CHESS_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    if (*chess_result != CHESS_SUCCESS) // CHESS_SUCCESS - if average playing time was returned successfully.
    {
        return ERROR_CODE; // from my understanding we can return whatever we want
    }
    return result;
}

static ChessResult chessSavePlayersLevelsParametersCheck(ChessSystem chess, FILE* file)
{
    if (chess == NULL || file == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    return CHESS_SUCCESS;
}

static ChessResult chessUpdatePlayerStats(ChessSystem chess)
{
    assert(chess != NULL);
    MAP_FOREACH (int * ,player_id, chess->players)
    {
        int* player_tournaments = playersMapGetTournaments(chess->players, *player_id);
        if (player_tournaments == NULL)
        {
            // should think what to return NULL POINTER/ MEMORY FAIL or something else;
            // because it's possible that the chess is not null but one of the players inside it points to null by purpose.
            // in case it's a CHESS_OUT_OF_MEMORY we need to terminate the program.
            free(player_id);
            return CHESS_OUT_OF_MEMORY;
        }
        int num_of_player_tournaments = 0, k = 0;
        while (player_tournaments[k++])
        {
            num_of_player_tournaments++;
        }
        for (int i = 0; i < num_of_player_tournaments; i++)
        {
            int *player_games = playersMapGetGamesInTournament(chess->players, *player_id, player_tournaments[i]);
            if (player_games == NULL)
            {
                // should think what to return NULL POINTER/ MEMORY FAIL or something else;
                // because it's possible that the chess is not null but one of the players inside it points to null by purpose.
                // in case it's a CHESS_OUT_OF_MEMORY we need to terminate the program.
                free(player_id);
                free(player_tournaments);
                return CHESS_OUT_OF_MEMORY;
            }

            int num_of_games = playersMapGetMaxGamesForTournament(chess->players, *player_id, player_tournaments[i]);
            if (num_of_games == ERROR_CODE)
            {
                free(player_id);
                free(player_tournaments);
                free(player_games);
                return CHESS_OUT_OF_MEMORY;
            }
            for (int j = 0; j < num_of_games; j++)
            {
                if (player_games[j] == 0)
                {
                    break;
                }
                int game_result = tournamentTableGetPlayerResultInGame(chess->tournament_table,
                                                            player_tournaments[i], player_games[j], *player_id);
                chessUpdatePlayerWithGameResult(chess->players, *player_id, game_result);
            }
            free(player_games);
        }
        free(player_tournaments);
        free(player_id);
    }
    return CHESS_SUCCESS;
}

static void chessUpdatePlayerWithGameResult(Players players, PlayerID player_id, int game_result)
{
    // we receive result from OMRI's function AND need to be sure we got the same defines
    switch(game_result)
    {
        case (WIN):
            playersMapAddWin(players,player_id);
            break;
        case (TIE):
            playersMapAddTie(players,player_id);
            break;
        case (LOSE):
            playersMapAddLose(players,player_id);
            break;
        default:
            break;
    }
}

static int chessCalculatePlayerLevel(Players players, PlayerID player_id, int n)
{
    int num_of_wins = playersMapGetWins(players, player_id);
    int num_of_ties = playersMapGetTies(players, player_id);
    int num_of_loses = playersMapGetLoses(players, player_id);
    return (POINTS_PER_WIN * num_of_wins + POINTS_PER_LOSE * num_of_loses + POINTS_PER_TIE * num_of_ties)/ n ;
}

static void swap(double* x, double* y)
{
    double temp = *x;
    *x = *y;
    *y = temp;
}
static int bubble(double a[], int n)
{
    int i, swapped = 0;
    for (i = SIZE_OF_PAIR; i < n; i += SIZE_OF_PAIR)
    {
        if (a[i-1] > a[i+1])
        {
            swap(&a[i], &a[i-SIZE_OF_PAIR]);
            swap(&a[i+1], &a[i-1]);
            swapped = 1;
        }
        if (a[i-1] == a[i+1])
        {
            if (a[i-SIZE_OF_PAIR] < a[i])
            {
                swap(&a[i], &a[i-SIZE_OF_PAIR]);
                swap(&a[i+1], &a[i-1]);
                swapped = 1;
            }
        }
    }
    return swapped;
}

static void bubble_sort(double a[], int n) // need to remember that n here is 2n
{
    int not_sorted = 1;
    while ((n > 1) && not_sorted)
    {
        not_sorted = bubble(a, n);
        n -= SIZE_OF_PAIR;
    }
}

static double* chessCalculateAndSortRankings(Players players, int n)
{
    // we want to return a two list array of id's and levels (after we sort it)
    double *rankings_array = malloc(sizeof(*rankings_array)*2*n);
    if (rankings_array == NULL)
    {
        return NULL;
    }
    int i = 0;
    MAP_FOREACH (int * ,player_id, players)
    {
        rankings_array[i] = *player_id;
        rankings_array[i+1] = chessCalculatePlayerLevel(players, *player_id, n);
        i += SIZE_OF_PAIR;
        free(player_id);
    }
    bubble_sort(rankings_array, n * SIZE_OF_PAIR);
    return rankings_array;
}

static ChessResult chessPrintRankingsToFile(double a[], int n, FILE* file)
{
    for (int i = n-SIZE_OF_PAIR ; i >= 0 ; i -= SIZE_OF_PAIR)
    {
        if (fprintf(file, "%.0lf %.2lf\n", a[i], a[i+1]) == EOF)
        {
            free(a);
            return CHESS_SAVE_FAILURE;
        }
    }
    free(a);
    return CHESS_SUCCESS;
}

ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file) {
    ChessResult parameters_check_result = chessSavePlayersLevelsParametersCheck(chess, file);
    if (parameters_check_result != CHESS_SUCCESS)
    {
        return parameters_check_result;
    }
    ChessResult chess_result = chessUpdatePlayerStats(chess);
    if (chess_result == CHESS_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    /*int n = tournamentTableGetNumberOfGames(chess->tournament_table);
    double *ratings_array = chessCalculateAndSortRankings(chess->players, n);
    if (ratings_array == NULL)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    PlayersMapNullifyAllPlayerStats(chess->players);
    chess_result = chessPrintRankingsToFile(ratings_array, SIZE_OF_PAIR*n, file);*/
    return chess_result;
}

static ChessResult chessSaveTournamentStatisticsParametersCheck(ChessSystem chess)
{
    if(chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if(chess->tournament_ended == false)
    {
        return CHESS_NO_TOURNAMENTS_ENDED;
    }
    return CHESS_SUCCESS;
}

ChessResult chessSaveTournamentStatistics (ChessSystem chess, char* path_file)
{
    ChessResult parameter_check_result = chessSaveTournamentStatisticsParametersCheck(chess);
    if(parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentError check_result = tournamentTableGetStatsOfTournament(chess->tournament_table,path_file);
    if(check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    if(check_result == TOURNAMENT_SAVE_FAILURE)
    {
        return CHESS_SAVE_FAILURE;
    }
    return CHESS_SUCCESS;
}