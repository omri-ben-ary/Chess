#ifndef MAIN_C_PLAYER_STATS_H
#define MAIN_C_PLAYER_STATS_H

#include "tournaments_history_table.h"
#include <stdbool.h>

typedef struct PlayerStats_t *PlayerStats;

/**
 * playerStatsCreate: initializes the relevant player stats every time a player is being added to the system.
 * @return : an ADT of the relevant player stats if everything succeeded
 *           NULL pointer if memory allocation failed
 */
PlayerStats playerStatsCreate();

/**
 * playerStatsDestroy: destroy the player stats object and frees all the memory that was allocated.
 * @param player_stats : the element to destroy.
 */
void playerStatsDestroy(PlayerStats player_stats);

/**
 * playerStatsSearchForTournament : checks if a player has previous record for a tournament
 * @param player_stats : the player which we want to search for the tournament stats.
 * @param tournament_id: the tournament we want to search.
 * @return true - if tournament records are already exists.
 *         false - if these are the first tournament records for the player.
 */
bool playerStatsSearchForTournament(PlayerStats player_stats, TournamentID tournament_id);

/**
 * GameStatsAdd: add a game to a specific tournament inside the player records.
 * @param player_stats : the stats of the player to edit.
 * @param tournament_id : the tournament to add the game stats to.
 * @param game_id : the game id to add.
 * @param max_games_allowed : the maximum games that are allowed for a player in a given tournament.
 * @return TOURNAMENT_STATS_NULL_POINTER - if tournament is null.
 *         GAME_ID_IS_ALREADY_TAKEN - if game id is already exist in the array.
 *         TOURNAMENT_STATS_FULL_OF_GAMES - if the player played more games than allowed.
 *         GAME_STATS_ADD_SUCCESS - games stats were added successfully.
 */
TournamentStatsResult playerStatsAddGame(PlayerStats player_stats, int tournament_id,
                                         int game_id, int max_games_allowed);


/**
 * playerStatsInteriorCopy: creates a copy of a specific player's stats
 * @param player_stats : the stats we want to create a copy of.
 * @return copy of the player's stats if everything succeed
 *          NULL if there was any allocation memory fail or the player's stats are null
 */
PlayerStats playerStatsInteriorCopy(PlayerStats player_stats);

#endif //MAIN_C_PLAYER_STATS_H
