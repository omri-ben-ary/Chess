#ifndef MAIN_C_TOURNAMENT_HISTORY_H
#define MAIN_C_TOURNAMENT_HISTORY_H

#include <stdbool.h>

typedef struct TournamentStats_t *TournamentStats;

typedef enum TournamentStatsResult_t
{
    TOURNAMENT_STATS_OUT_OF_MEMORY,
    TOURNAMENT_STATS_NULL_POINTER,
    GAME_ID_IS_ALREADY_TAKEN,
    TOURNAMENT_STATS_FULL_OF_GAMES,
    GAME_STATS_ADD_SUCCESS
} TournamentStatsResult ;

/**
 * tournamentStatsCreate: initializes the relevant tournament stats every time a tournament is being created
 * such as the maximum allowed games and the list of games that the player was attended in
 * @param max_games_allowed : the amount of games that one player can play in a given tournament
 * @return : an ADT of the relevant tournament stats if everything succeeded
 *          NULL pointer if un positive amount of games was entered or memory allocation failed
 */
TournamentStats tournamentStatsCreate(int max_games_allowed);

/** playerPlayedMaxGamesCheck : check if the player already played the maximal amount of games.
 * @param tournament : the tournament we want to check how many possible games left to the player.
 * @return : true if the player played less games than he is able to.
 *           false if the player crossed the game limit,
 */
bool playerPlayedMaxGamesCheck(TournamentStats tournament);

/**
 * tournamentStatsGetMaxGamesAllowed : gets the maximum games allowed for one player to attend in given tournament.
 * @param tournament : the tournament which we want to understand his games limit .
 * @return : maximum games allowed in a given tournament.
 */
int tournamentStatsGetMaxGamesAllowed(TournamentStats tournament);

/**
 * gameStatsContainedCheck : checks if the games stats of a given game id is already stored.
 * @param tournament : the tournament which we want to search for the game stats.
 * @param game_id : game id to check if already contained.
 * @return true - if game id already exists.
 *         false - if game id is new.
 */
bool gameStatsContainedCheck(TournamentStats tournament, int game_id);

/**
 * GameStatsAdd: add game stats of a new game.
 * @param tournament : the tournament to add the game stats to.
 * @param game_id : the game id of given game.
 * @return TOURNAMENT_STATS_NULL_POINTER - if tournament is null.
 *         GAME_ID_IS_ALREADY_TAKEN - if game id is already exist in the array.
 *         TOURNAMENT_STATS_FULL_OF_GAMES - if the player played more games than allowed.
 *         GAME_STATS_ADD_SUCCESS - games stats were added successfully.
 */
TournamentStatsResult gameStatsAdd(TournamentStats tournament, int game_id);

/**
 * tournamentStatsDestroy: destroy the tournament stats object and frees all the memory that was allocated.
 * @param tournament : the tournament to destroy.
 */
void tournamentStatsDestroy(TournamentStats tournament);

/**
 * tournamentStatsInteriorCopy: creates a copy of a given tournament stats
 * @param tournament : the tournament we want to create a copy of
 * @return copy of the tournament if everything succeed
 *          NULL if there was any allocation memory fail or the tournament is null
 */
TournamentStats tournamentStatsInteriorCopy(TournamentStats tournament);

/**
 * tournamentStatsGetGames: create a list of the games that a given player played in a given tournament.
 * @param tournament : the tournament which we want to get the games the player played in.
 * @return a list of the games that a player played in a given tournament
 */
int* tournamentStatsGetGames(TournamentStats tournament);


#endif //MAIN_C_TOURNAMENT_HISTORY_H

