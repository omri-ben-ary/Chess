#ifndef MAIN_C_PLAYERTOURNAMENTSTATS_H
#define MAIN_C_PLAYERTOURNAMENTSTATS_H

#include <stdbool.h>

typedef struct PlayerTournamentStats_t *PlayerTournamentStats;

typedef enum PlayerTournamentStatsResult_t
{
    PLAYER_TOURNAMENT_STATS_OUT_OF_MEMORY,
    PLAYER_TOURNAMENT_STATS_PUT_SUCCESS,
    PLAYER_TOURNAMENT_STATS_GAME_ADD_SUCCESS,
    PLAYER_TOURNAMENT_STATS_GAME_REMOVE_SUCCESS,
    PLAYER_TOURNAMENT_STATS_IS_EMPTY
} PlayerTournamentStatsResult ;

/**
 * playerTournamentStatsCreate: initializes the relevant tournament stats every time a tournament is being created
 * such as the maximum allowed games and the list of games that the player was attended in
 * @param max_games_allowed : the amount of games that one player can play in a given tournament
 * @return : an ADT of the relevant tournament stats if everything succeeded
 *          NULL pointer if un positive amount of games was entered or memory allocation failed
 */
PlayerTournamentStats playerTournamentStatsCreate(int max_games_allowed);

/**
 * playerTournamentStatsDestroy: destroy the tournament stats object and frees all the memory that was allocated.
 * @param tournament : the tournament to destroy.
 */
void playerTournamentStatsDestroy(PlayerTournamentStats tournament);

/** playerTournamentStatsMaxGamesCheck : check if the player already played the maximal amount of games.
 * @param tournament : the tournament we want to check how many possible games left to the player.
 * @return : true if the player played less games than he is able to.
 *           false if the player crossed the game limit,
 */
bool playerTournamentStatsMaxGamesCheck(PlayerTournamentStats tournament);

/**
 * playerTournamentStatsGetMaxGamesAllowed : gets the maximum games allowed for one player to attend
 * in given tournament.
 * @param tournament : the tournament which we want to understand his games limit .
 * @return : maximum games allowed in a given tournament.
 *           -1 if tournament is NULL
 */
int playerTournamentStatsGetMaxGamesAllowed(PlayerTournamentStats tournament);


/**
 * playerTournamentStatsAddGameStats: add game stats of a new game.
 * @param tournament : the tournament to add the game stats to.
 * @param game_id : the game id of given game.
 * @return GAME_STATS_ADD_SUCCESS - games stats were added successfully.
 */
PlayerTournamentStatsResult playerTournamentStatsAddGameStats(PlayerTournamentStats tournament, int game_id);

/**
 * playerTournamentStatsInteriorCopy: creates a copy of a given tournament stats
 * @param tournament : the tournament we want to create a copy of
 * @return copy of the tournament if everything succeed
 *          NULL if there was any allocation memory fail or the tournament is null
 */
PlayerTournamentStats playerTournamentStatsInteriorCopy(PlayerTournamentStats tournament);

/**
 * playerTournamentStatsGetGames: create a list of the games that a given player played in a given tournament.
 * @param tournament : the tournament which we want to get the games the player played in.
 * @return a list of the games that a player played in a given tournament
 */
int* playerTournamentStatsGetGames(PlayerTournamentStats tournament);

/**
 * playerTournamentStatsRemoveGame: remove game from a given tournament.
 * @param tournament : the tournament to remove the game from.
 * @param game_id : the game to remove.
 * @return PLAYER_TOURNAMENT_STATS_IS_EMPTY : if it's the only game in the tournament.
 *         PLAYER_TOURNAMENT_STATS_GAME_REMOVE_SUCCESS : if everything succeeded.
 */
PlayerTournamentStatsResult playerTournamentStatsRemoveGame(PlayerTournamentStats tournament, int game_id);

#endif //MAIN_C_PLAYERTOURNAMENTSTATS_H

