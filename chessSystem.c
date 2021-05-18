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
// OMRI should add his defines here

struct chess_system_t{
    Players players;
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

// FUNCTIONS IMPLEMENTATION (STATIC FUNCTIONS (HELPERS) BEFORE THE FUNCTION THEY RELATE TO):

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
    if (chessContainPlayer(chess, player_id))
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
    double average_play_time = 0;
    for (int i = 0; i < num_of_player_tournaments; i++)
    {
        int *player_games = playersMapGetGamesInTournament(chess->players, player_id, player_tournaments[i]);
        if (player_games == NULL)
        {
            // should think what to return NULL POINTER/ MEMORY FAIL or something else;
            // because it's possible that the chess is not null but one of the players inside it points to null by purpose.
            // in case it's a CHESS_OUT_OF_MEMORY we need to terminate the program.
            return ERROR_CODE;
        }
        int num_of_games = playersMapGetMaxGamesForTournament(chess->players, player_id, player_tournaments[i]);
        if (num_of_games == ERROR_CODE)
        {
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
               // specific code for removing player
               // i pass him: player_tournaments[i] && player_games[j];
               // need to check tournament is still alive and then remove player from game and change game stats.
           }
           if (chosen_function == CALCULATE_AVERAGE_PLAY_TIME)
           {
               // specific code for calculating average time
               // i pass him: player_tournaments[i] && player_games[j];
               // need to check tournament and game are still alive and send me the total time of the game.
           }
        }
        free(player_games);
    }
    free(player_tournaments);
    *chess_result = CHESS_SUCCESS;
    return average_play_time;
}

ChessResult chessRemovePlayer(ChessSystem chess, int player_id)
{
    ChessResult chess_result; // don't sure about that line, should i malloc it?
    chessCalculateAveragePlayTimeOrRemovePlayer(chess, player_id, &chess_result, CALCULATE_AVERAGE_PLAY_TIME);
    playersMapRemove(chess->players, player_id);
    return chess_result;
}


double chessCalculateAveragePlayTime (ChessSystem chess, int player_id, ChessResult* chess_result)
{
    double result = chessCalculateAveragePlayTimeOrRemovePlayer(chess, player_id, chess_result, REMOVE_PLAYER_ID);
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
                return CHESS_OUT_OF_MEMORY;
            }

            int num_of_games = playersMapGetMaxGamesForTournament(chess->players, *player_id, player_tournaments[i]);
            if (num_of_games == ERROR_CODE)
            {
                return CHESS_OUT_OF_MEMORY;
            }
            for (int j = 0; j < num_of_games; j++)
            {
                if (player_games[j] == 0)
                {
                    break;
                }
                int game_result = tournamentGetPlayerResult(tournament, player_tournaments[i], player_games[j], *player_id); // OMRI
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
    int i = 0;
    MAP_FOREACH (int * ,player_id, players)
    {
        rankings_array[i] = *player_id;
        rankings_array[i+1] = chessCalculatePlayerLevel(players, *player_id, n);
        i+=SIZE_OF_PAIR;
        free(player_id);
    }
    bubble_sort(rankings_array, n * SIZE_OF_PAIR);
    // sort equal rankings;
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

/**
 * chessSavePlayersLevels: prints the rating of all players in the system as
 * explained in the *.pdf
 *
 * @param chess - a chess system. Must be non-NULL.
 * @param file - an open, writable output stream, to which the ratings are printed.
 * @return
 *     CHESS_NULL_ARGUMENT - if chess is NULL.
 *     CHESS_SAVE_FAILURE - if an error occurred while saving.
 *     CHESS_SUCCESS - if the ratings was printed successfully.
 */
ChessResult chessSavePlayersLevels (ChessSystem chess, FILE* file) {
    ChessResult parameters_check_result = chessSavePlayersLevelsParametersCheck(chess, file);
    if (parameters_check_result != CHESS_SUCCESS)
    {
        return parameters_check_result;
    }
    ChessResult chess_result = chessUpdatePlayerStats(chess);
    if (chess_result != CHESS_SUCCESS)
    {
        return chess_result;
    }
    int n = tournametTableGetNumberOfGames(tournament); // OMRI
    double *ratings_array = chessCalculateAndSortRankings(chess->players, n);
    PlayersMapNullifyAllPlayerStats(chess->players); // should think if it's cool that it's void (might be an issue inside)
    chess_result = chessPrintRankingsToFile(ratings_array, SIZE_OF_PAIR*n, file);
    return chess_result;
}