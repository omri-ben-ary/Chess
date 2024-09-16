#include "chessSystem.h"
#include "playersMap.h"
#include "tournament.h"
#include <assert.h>
#include <stdlib.h>

#define ERROR_CODE 0
#define SIZE_OF_PAIR 2
#define WIN 0
#define LOSE 1
#define TIE 2
#define POINTS_PER_WIN 6
#define POINTS_PER_TIE 2
#define POINTS_PER_LOSE (-10)
#define FIRST_CAPITAL_LETTER 'A'
#define LAST_CAPITAL_LETTER 'Z'
#define FIRST_SMALL_LETTER 'a'
#define LAST_SMALL_LETTER 'z'
#define SPACE_CHAR ' '

struct chess_system_t{
    Players players;
    TournamentTable tournament_table;
    int num_of_ended_tournament;
};

// STATIC FUNCTION PROTOTYPING:

// static functions for #chessAddTournament:
static bool chessLocationNameCheck(const char* name);
static ChessResult chessAddTournamentParametersCheck(ChessSystem chess, int tournament_id,
                                                     int max_games_per_player, const char* tournament_location);

// static functions for #chessAddGame:
static ChessResult chessAddGameParametersCheck(ChessSystem chess, int tournament_id, int first_player,
                                               int second_player, Winner winner, int play_time);
static GameResult chessAddGameCheckForWinner(Winner winner);
static void chessAddGameUndoActions(TournamentData tournament_data, int num_of_players_added, int game_id);

// static functions for #chessRemoveTournament:
static ChessResult chessRemoveTournamentParametersCheck(ChessSystem chess, int tournament_id);

// static functions for #chessRemovePlayer:
static ChessResult chessRemovePlayerParametersCheck(ChessSystem chess, int player_id);
static void chessRemovePlayerFromEachTournament(
        ChessSystem chess,int player_id, int num_of_player_tournaments,
        int *player_tournaments, int **list_of_pointers_to_tournament_games);
static ChessResult chessRemovePlayerManage(ChessSystem chess, int player_id);

// static functions for #chessEndTournament:
static ChessResult chessEndTournamentParametersCheck(ChessSystem chess, int tournament_id);

// static functions for #chessCalculateAveragePlayTime :
static ChessResult chessCalculateAveragePlayTimeParametersCheck(ChessSystem chess, int player_id);
static double chessCalculateAveragePlayTimeInTournaments(ChessSystem chess,int player_id, ChessResult* chess_result);

// static functions for #chessSavePlayerLevels:
static ChessResult chessSavePlayersLevelsParametersCheck(ChessSystem chess, FILE* file);
static ChessResult chessUpdatePlayerStats(ChessSystem chess);
static void chessUpdatePlayerWithGameResult(Players players, PlayerID player_id, int game_result);
static double chessCalculatePlayerLevel(Players players, PlayerID player_id);
static void chessSwapDoubles(double* x, double* y);
static int chessBubblePlayersRankings(double a[], int n);
static void chessBubbleSortPlayersRankings(double a[], int n);
static double* chessCalculateAndSortRankings(Players players, int n);
static ChessResult chessPrintRankingsToFile(Players players, double a[], int n, FILE* file);

// static functions for #chessSaveTournamentStatistics:
static ChessResult chessSaveTournamentStatisticsParametersCheck(ChessSystem chess);

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
    chess->num_of_ended_tournament=0;
    return chess;
}

void chessDestroy(ChessSystem chess)
{
    if (chess == NULL)
    {
        return;
    }
    playersMapDestroy(chess->players);
    tournamentTableDestroy(chess->tournament_table);
    free(chess);
}

static bool chessLocationNameCheck(const char* name)
{
    if (strlen(name) == 0)
    {
        return false;
    }

    if (*name < FIRST_CAPITAL_LETTER || *name > LAST_CAPITAL_LETTER)
    {
        return false;
    }
    while (*(++name))
    {
        if (*name < FIRST_SMALL_LETTER || *name > LAST_SMALL_LETTER)
        {
            if (*name != SPACE_CHAR)
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
    if (chess == NULL || tournament_location == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if (tournamentTableContains(chess->tournament_table, tournament_id))
    {
        return CHESS_TOURNAMENT_ALREADY_EXISTS;
    }
    if (chessLocationNameCheck(tournament_location) == false)
    {
        return CHESS_INVALID_LOCATION;
    }
    if (max_games_per_player <= 0)
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
    if (parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentData tournament_data = tournamentDataCreate(tournament_location, max_games_per_player);
    TournamentError check_result = tournamentTableAddOrEditTournament(
            chess->tournament_table, tournament_id, tournament_data);
    tournamentDataDestroy(tournament_data);
    if (check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    assert(check_result != TOURNAMENT_NULL_ARGUMENT);
    return CHESS_SUCCESS;
}

static ChessResult chessAddGameParametersCheck(ChessSystem chess, int tournament_id, int first_player,
                                               int second_player, Winner winner, int play_time)
{
    if (chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0 || first_player <= 0 || second_player <= 0 || first_player == second_player)
    {
        return CHESS_INVALID_ID;
    }
    if (winner != FIRST_PLAYER && winner != SECOND_PLAYER && winner != DRAW)
    {
        return CHESS_INVALID_ID;
    }
    if (tournamentTableContains(chess->tournament_table, tournament_id) == false)
    {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    if (tournamentDataGetWinnerId(tournament_data) != 0)
    {
        return CHESS_TOURNAMENT_ENDED;
    }
    if (gameTableCheckIfPlayersMetAlready(game_table, first_player, second_player))
    {
        return CHESS_GAME_ALREADY_EXISTS;
    }
    if (play_time < 0)
    {
        return CHESS_INVALID_PLAY_TIME;
    }
    if (!(playersMapCheckForMaxGamesOfPlayer(chess->players, first_player, tournament_id)))
    {
        return CHESS_EXCEEDED_GAMES;
    }
    if (!(playersMapCheckForMaxGamesOfPlayer(chess->players, second_player, tournament_id)))
    {
        return CHESS_EXCEEDED_GAMES;
    }
    return CHESS_SUCCESS;
}

static GameResult chessAddGameCheckForWinner(Winner winner)
{
    if (winner == FIRST_PLAYER)
    {
        return FIRST;
    }
    else if (winner == SECOND_PLAYER)
    {
        return SECOND;
    }
    return GAME_DRAW;
}

static void chessAddGameUndoActions(TournamentData tournament_data, int num_of_players_added, int game_id)
{
    tournamentDataSetNumberOfPlayers(
            tournament_data,tournamentDataGetNumberOfPlayers(tournament_data)-num_of_players_added);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    gameTableRemoveGame(game_table, game_id);
}

ChessResult chessAddGame(ChessSystem chess, int tournament_id, int first_player,
                         int second_player, Winner winner, int play_time)
{
    ChessResult parameter_check_result = chessAddGameParametersCheck(
            chess, tournament_id, first_player, second_player, winner, play_time);
    if (parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    int game_id = tournamentDataGetGameIndex(tournament_data);
    int max_games_for_tournament = tournamentDataGetMaxGames(tournament_data);
    GameResult game_result = chessAddGameCheckForWinner(winner);
    int num_of_players_added = 0;
    TournamentError check_result = tournamentTableAddGame(chess->tournament_table, tournament_id, first_player,
                                                           second_player,game_result,play_time,&num_of_players_added);
    if (check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    assert(check_result != TOURNAMENT_NULL_ARGUMENT);
    PlayerStatsResult first_player_stats_result = playersMapAddGameStats(
            chess->players, first_player, tournament_id, game_id, max_games_for_tournament);
    if (first_player_stats_result == PLAYER_STATS_OUT_OF_MEMORY)
    {
        chessAddGameUndoActions(tournament_data, num_of_players_added, game_id);
        return CHESS_OUT_OF_MEMORY;
    }
    PlayerStatsResult second_player_stats_result = playersMapAddGameStats(
            chess->players, second_player, tournament_id, game_id, max_games_for_tournament);
    if (second_player_stats_result == PLAYER_STATS_OUT_OF_MEMORY)
    {
        playersMapRemoveGameFromStats(chess->players, first_player, tournament_id, game_id);
        chessAddGameUndoActions(tournament_data, num_of_players_added, game_id);
        return CHESS_OUT_OF_MEMORY;
    }
    return CHESS_SUCCESS;
}

static ChessResult chessRemoveTournamentParametersCheck(ChessSystem chess, int tournament_id)
{
    if (chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if (tournamentTableContains(chess->tournament_table, tournament_id) == false)
    {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    return CHESS_SUCCESS;
}

ChessResult chessRemoveTournament (ChessSystem chess, int tournament_id)
{
    ChessResult parameter_check_result = chessRemoveTournamentParametersCheck(chess, tournament_id);
    if (parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    MAP_FOREACH(int*, iterator, game_table)
    {
         if (iterator == NULL)
         {
            break;
         }
        GameData game_data = gameTableGetGameData(game_table, *iterator);
        int player1_id = gameDataGetPlayer(game_data, PLAYER1);
        playersMapRemoveTournament(chess->players, player1_id, tournament_id);
        int player2_id = gameDataGetPlayer(game_data, PLAYER2);
        playersMapRemoveTournament(chess->players, player2_id, tournament_id);
        free(iterator);
    }
    if(tournamentDataGetWinnerId(tournament_data) != 0)
    {
        chess->num_of_ended_tournament--;
    }
    tournamentTableDeleteTournament(chess->tournament_table, tournament_id);
    return CHESS_SUCCESS;
}

static ChessResult chessRemovePlayerParametersCheck(ChessSystem chess, int player_id)
{
    if (chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (player_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if (!(playersMapContain(chess->players, player_id)))
    {
        return CHESS_PLAYER_NOT_EXIST;
    }
    return CHESS_SUCCESS;
}

static void chessRemovePlayerFromEachTournament(
        ChessSystem chess,int player_id, int num_of_player_tournaments,
        int *player_tournaments, int **list_of_pointers_to_tournament_games)
{
    for (int i = 0; i < num_of_player_tournaments; i++)
    {
        TournamentData tournament_data = tournamentTableGetTournamentData(
                chess->tournament_table, player_tournaments[i]);
        if (tournamentDataGetWinnerId(tournament_data) != 0)
        {
            continue;
        }
        int *player_games = list_of_pointers_to_tournament_games[i];
        int num_of_games = playersMapGetMaxGamesForTournament(chess->players, player_id, player_tournaments[i]);
        for (int j = 0; j < num_of_games; j++)
        {
            if (player_games[j] == 0)
            {
                break;
            }
            tournamentTableRemovePlayerInGame(
                    chess->tournament_table, player_tournaments[i], player_games[j], player_id);
        }
    }
    for (int i = 0; i < num_of_player_tournaments; i++)
    {
        free(list_of_pointers_to_tournament_games[i]);
    }
    free(player_tournaments);
    free(list_of_pointers_to_tournament_games);
}

static ChessResult chessRemovePlayerManage(ChessSystem chess, int player_id)
{
    int *player_tournaments = playersMapGetTournaments(chess->players, player_id);
    if (player_tournaments == NULL)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    int num_of_player_tournaments = playersMapCalculateNumOfPlayerTournaments(player_tournaments);
    int **list_of_pointers_to_tournament_games = malloc(
            sizeof(*list_of_pointers_to_tournament_games) * (num_of_player_tournaments));
    if (list_of_pointers_to_tournament_games == NULL)
    {
        free(player_tournaments);
        return CHESS_OUT_OF_MEMORY;
    }
    for (int i = 0; i < num_of_player_tournaments ; i++)
    {
        list_of_pointers_to_tournament_games[i] = playersMapGetGamesInTournament(
                chess->players, player_id, player_tournaments[i]);
        if (list_of_pointers_to_tournament_games[i] == NULL)
        {
            free(player_tournaments);
            for (int j = 0; j < i; j++)
            {
                free(list_of_pointers_to_tournament_games[j]);
            }
            free(list_of_pointers_to_tournament_games);
            return CHESS_OUT_OF_MEMORY;
        }
    }
    chessRemovePlayerFromEachTournament(chess,player_id,num_of_player_tournaments,
                                         player_tournaments, list_of_pointers_to_tournament_games);
    return CHESS_SUCCESS;
}

ChessResult chessRemovePlayer(ChessSystem chess, int player_id)
{
    ChessResult parameters_check_result = chessRemovePlayerParametersCheck(chess, player_id);
    if (parameters_check_result != CHESS_SUCCESS)
    {
        return parameters_check_result;
    }
    PlayerStats player_stats = playersMapGetStats(chess->players, player_id);
    if (playerStatsHasNoTournamentsCheck(player_stats) == true)
    {
        playersMapRemove(chess->players, player_id);
        return CHESS_SUCCESS;
    }
    ChessResult chess_result = chessRemovePlayerManage(chess, player_id);
    if (chess_result == CHESS_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    playersMapRemove(chess->players, player_id);
    return CHESS_SUCCESS;
}

static ChessResult chessEndTournamentParametersCheck(ChessSystem chess, int tournament_id)
{
    if (chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (tournament_id <= 0)
    {
        return CHESS_INVALID_ID;
    }
    if (tournamentTableContains(chess->tournament_table, tournament_id) == false)
    {
        return CHESS_TOURNAMENT_NOT_EXIST;
    }
    TournamentData tournament_data = tournamentTableGetTournamentData(chess->tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    if (tournamentDataGetWinnerId(tournament_data) != 0)
    {
        return CHESS_TOURNAMENT_ENDED;
    }
    if (gameTableGetSize(game_table) == 0)
    {
        return CHESS_NO_GAMES;
    }
    return CHESS_SUCCESS;
}

ChessResult chessEndTournament (ChessSystem chess, int tournament_id)
{
    ChessResult parameter_check_result = chessEndTournamentParametersCheck(chess, tournament_id);
    if (parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentError check_result = tournamentTableEndTournament(chess->tournament_table,tournament_id);
    if (check_result == TOURNAMENT_OUT_OF_MEMORY)
    {
        return CHESS_OUT_OF_MEMORY;
    }
    chess->num_of_ended_tournament++;
    return CHESS_SUCCESS;
}

static ChessResult chessCalculateAveragePlayTimeParametersCheck(ChessSystem chess, int player_id)
{
    return chessRemovePlayerParametersCheck(chess, player_id);
}

static double chessCalculateAveragePlayTimeInTournaments(ChessSystem chess, int player_id, ChessResult* chess_result)
{
    int* player_tournaments = playersMapGetTournaments(chess->players, player_id);
    if (player_tournaments == NULL)
    {
        *chess_result = CHESS_OUT_OF_MEMORY;
        return ERROR_CODE;
    }
    int num_of_player_tournaments = playersMapCalculateNumOfPlayerTournaments(player_tournaments);
    double average_play_time = 0;
    int n = 0;
    for (int i = 0; i < num_of_player_tournaments; i++)
    {
        int *player_games = playersMapGetGamesInTournament(chess->players, player_id, player_tournaments[i]);
        if (player_games == NULL)
        {
            free(player_tournaments);
            *chess_result = CHESS_OUT_OF_MEMORY;
            return ERROR_CODE;
        }
        int num_of_games = playersMapGetMaxGamesForTournament(chess->players, player_id, player_tournaments[i]);
        for (int j = 0; j < num_of_games; j++)
        {
            if (player_games[j] == 0)
            {
                break;
            }
            n++;
            double last_play_time = tournamentTableGetGameTime(
                    chess->tournament_table, player_tournaments[i], player_games[j]);
            double previous_average_play_time = average_play_time;
            average_play_time = (previous_average_play_time*(n-1))/n + last_play_time/n ;
        }
        free(player_games);
    }
    free(player_tournaments);
    *chess_result = CHESS_SUCCESS;
    return average_play_time;
}

double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result)
{
    *chess_result = chessCalculateAveragePlayTimeParametersCheck(chess, player_id);
    if (*chess_result != CHESS_SUCCESS)
    {
        return ERROR_CODE;
    }
    PlayerStats player_stats = playersMapGetStats(chess->players, player_id);
    if (playerStatsHasNoTournamentsCheck(player_stats) == true)
    {
        return 0;
    }
    return chessCalculateAveragePlayTimeInTournaments(chess, player_id, chess_result);
}

static ChessResult chessSavePlayersLevelsParametersCheck(ChessSystem chess, FILE* file)
{
    if (chess == NULL || file == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    return CHESS_SUCCESS;
}

static void chessUpdatePlayerWithGameResult(Players players, PlayerID player_id, int game_result)
{
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

static ChessResult chessUpdatePlayerStats(ChessSystem chess)
{
    assert(chess != NULL);
    MAP_FOREACH (int * ,player_id, chess->players)
    {
        if (player_id == NULL)
        {
            break;
        }
        PlayerStats player_stats = playersMapGetStats(chess->players, *player_id);
        if (playerStatsHasNoTournamentsCheck(player_stats) == true)
        {
            free(player_id);
            continue;
        }
        int* player_tournaments = playersMapGetTournaments(chess->players, *player_id);
        if (player_tournaments == NULL)
        {
            free(player_id);
            return CHESS_OUT_OF_MEMORY;
        }
        int num_of_player_tournaments = playersMapCalculateNumOfPlayerTournaments(player_tournaments);
        for (int i = 0; i < num_of_player_tournaments; i++)
        {
            int *player_games = playersMapGetGamesInTournament(chess->players, *player_id, player_tournaments[i]);
            if (player_games == NULL)
            {
                free(player_id);
                free(player_tournaments);
                return CHESS_OUT_OF_MEMORY;
            }
            int num_of_games = playersMapGetMaxGamesForTournament(chess->players, *player_id, player_tournaments[i]);
            for (int j = 0; j < num_of_games; j++)
            {
                if (player_games[j] == 0)
                {
                    break;
                }
                int game_result = tournamentTableGetPlayerResultInGame(
                        chess->tournament_table,player_tournaments[i], player_games[j], *player_id);
                chessUpdatePlayerWithGameResult(chess->players, *player_id, game_result);
            }
            free(player_games);
        }
        free(player_tournaments);
        free(player_id);
    }
    return CHESS_SUCCESS;
}

static double chessCalculatePlayerLevel(Players players, PlayerID player_id)
{
    int num_of_wins = playersMapGetAmountOf(players, player_id, WIN);
    int num_of_ties = playersMapGetAmountOf(players, player_id, TIE);
    int num_of_loses = playersMapGetAmountOf(players, player_id, LOSE);
    int n = num_of_wins + num_of_ties + num_of_loses;
    if (n == 0)
    {
        return 0;
    }
    return (POINTS_PER_WIN * num_of_wins + POINTS_PER_LOSE * num_of_loses + POINTS_PER_TIE * num_of_ties)/ (double)n;
}

static void chessSwapDoubles(double* x, double* y)
{
    double tmp = *x;
    *x = *y;
    *y = tmp;
}

static int chessBubblePlayersRankings(double a[], int n)
{
    int i, swapped = 0;
    for (i = SIZE_OF_PAIR; i < n; i += SIZE_OF_PAIR)
    {
        if (a[i-1] > a[i+1])
        {
            chessSwapDoubles(&a[i], &a[i-SIZE_OF_PAIR]);
            chessSwapDoubles(&a[i+1], &a[i-1]);
            swapped = 1;
        }
        if (a[i-1] == a[i+1])
        {
            if (a[i-SIZE_OF_PAIR] < a[i])
            {
                chessSwapDoubles(&a[i], &a[i-SIZE_OF_PAIR]);
                chessSwapDoubles(&a[i+1], &a[i-1]);
                swapped = 1;
            }
        }
    }
    return swapped;
}

static void chessBubbleSortPlayersRankings(double a[], int n)
{
    assert(a != NULL);
    int not_sorted = 1;
    while ((n > 1) && not_sorted)
    {
        not_sorted = chessBubblePlayersRankings(a, n);
        n -= SIZE_OF_PAIR;
    }
}

static double* chessCalculateAndSortRankings(Players players, int n)
{
    double *rankings_array = malloc(sizeof(*rankings_array) * SIZE_OF_PAIR * n);
    if (rankings_array == NULL)
    {
        return NULL;
    }
    for (int j = 0 ; j < (n * SIZE_OF_PAIR) ; j ++)
    {
        rankings_array[j] = 0;
    }
    int i = 0;
    MAP_FOREACH (int * ,player_id, players)
    {
        if (player_id == NULL)
        {
            break;
        }
        rankings_array[i] = *player_id;
        rankings_array[i+1] = chessCalculatePlayerLevel(players, *player_id);
        i += SIZE_OF_PAIR;
        free(player_id);
    }
    chessBubbleSortPlayersRankings(rankings_array, n * SIZE_OF_PAIR);
    return rankings_array;
}

static ChessResult chessPrintRankingsToFile(Players players, double a[], int n, FILE* file)
{
    for (int i = n-SIZE_OF_PAIR ; i >= 0 ; i -= SIZE_OF_PAIR)
    {
        PlayerStats player_stats = playersMapGetStats(players, (int)a[i]);
        if (playerStatsHasNoTournamentsCheck(player_stats) == true)
        {
            continue;
        }
        if (fprintf(file, "%.0lf %.2lf\n", a[i], a[i+1]) == EOF)
        {
            free(a);
            return CHESS_SAVE_FAILURE;
        }
    }
    free(a);
    return CHESS_SUCCESS;
}

ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file)
{
    ChessResult parameters_check_result = chessSavePlayersLevelsParametersCheck(chess, file);
    if (parameters_check_result != CHESS_SUCCESS)
    {
        return parameters_check_result;
    }
    ChessResult chess_result = chessUpdatePlayerStats(chess);
    if (chess_result == CHESS_OUT_OF_MEMORY)
    {
        PlayersMapNullifyAllPlayerStats(chess->players);
        return CHESS_OUT_OF_MEMORY;
    }
    int total_number_of_players = playersMapGetNumberOfPlayers(chess->players);
    if (total_number_of_players == 0)
    {
        if (fprintf(file, "\n") == EOF)
        {
            return CHESS_SAVE_FAILURE;
        }
        return CHESS_SUCCESS;
    }
    double *ratings_array = chessCalculateAndSortRankings(chess->players, total_number_of_players);
    if (ratings_array == NULL)
    {
        PlayersMapNullifyAllPlayerStats(chess->players);
        return CHESS_OUT_OF_MEMORY;
    }
    PlayersMapNullifyAllPlayerStats(chess->players);
    chess_result = chessPrintRankingsToFile(chess->players, ratings_array,
                                            SIZE_OF_PAIR*total_number_of_players, file);
    return chess_result;
}

static ChessResult chessSaveTournamentStatisticsParametersCheck(ChessSystem chess)
{
    if (chess == NULL)
    {
        return CHESS_NULL_ARGUMENT;
    }
    if (chess->num_of_ended_tournament == 0)
    {
        return CHESS_NO_TOURNAMENTS_ENDED;
    }
    return CHESS_SUCCESS;
}

ChessResult chessSaveTournamentStatistics (ChessSystem chess, char* path_file)
{
    ChessResult parameter_check_result = chessSaveTournamentStatisticsParametersCheck(chess);
    if (parameter_check_result != CHESS_SUCCESS)
    {
        return parameter_check_result;
    }
    TournamentError check_result = tournamentTableGetStatsOfTournament(chess->tournament_table,path_file);
    if (check_result == TOURNAMENT_SAVE_FAILURE)
    {
        return CHESS_SAVE_FAILURE;
    }
    return CHESS_SUCCESS;
}