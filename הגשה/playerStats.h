#ifndef MAIN_C_PLAYERSTATS_H
#define MAIN_C_PLAYERSTATS_H

#include "playerTournamentsMap.h"
#include <stdbool.h>

typedef struct PlayerStats_t *PlayerStats;

typedef enum PlayerStatsResult_t
{
    PLAYER_STATS_OUT_OF_MEMORY,
    PLAYER_STATS_NULL_POINTER,
    PLAYER_STATS_GAME_ADD_SUCCESS,
    PLAYER_STATS_NOT_EXIST,
    PLAYER_STATS_REMOVE_SUCCESS,
    PLAYER_STATS_PUT_SUCCESS
} PlayerStatsResult ;

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
 * playersStatsCheckForMaxGamesOfPlayer: check if a given player can still play in new games in the tournament.
 * @param player_stats : the player we want to check his game limit.
 * @param tournament_id : the id of the tournament we want to check if the player crossed the game limit inside.
 * @return true - if the player can play in new games.
 *         false - if the player reached the maximum game's limit.
 */
bool playersStatsCheckForMaxGamesOfPlayer(PlayerStats player_stats, TournamentID tournament_id);

/**
 * GameStatsAdd: add a game to a specific tournament inside the player records.
 * @param player_stats : the stats of the player to edit.
 * @param tournament_id : the tournament to add the game stats to.
 * @param game_id : the game id to add.
 * @param max_games_allowed : the maximum games that are allowed for a player in a given tournament.
 * @return PLAYER_STATS_OUT_OF_MEMORY - if there was memory fail.
 *         PLAYER_STATS_GAME_ADD_SUCCESS - games stats were added successfully.
 */
PlayerStatsResult playerStatsAddGame(PlayerStats player_stats, int tournament_id,
                                         int game_id, int max_games_allowed);

/**
 * playerStatsInteriorCopy: creates a copy of a specific player's stats
 * @param player_stats : the stats we want to create a copy of.
 * @return copy of the player's stats if everything succeed
 *          NULL if there was any allocation memory fail or the player's stats are null
 */
PlayerStats playerStatsInteriorCopy(PlayerStats player_stats);

/**
 * playerStatsRemoveTournament: check if an tournament id exists in player's records. if it does - it deletes it.
 * @param player_stats : the element which we want to delete the records of.
 * @param tournament_id : the id of the tournament we want to delete.
 */
void playerStatsRemoveTournament (PlayerStats player_stats, TournamentID tournament_id);

/**
 * playerStatsGetTournaments : get a list of the games a given player has taken part in a given tournament.
 * @param player_stats : the player we want to get the games he was part of in a given tournament.
 * @param tournament_id : the id of the tournament we want to find the games the given player has taken part in.
 * @return list of the games a given player has taken player in a given tournament.
 */
int* playerStatsGetGamesInTournament(PlayerStats player_stats, TournamentID tournament_id);

/**
 * playerStatsGetTournaments: get a list of the tournaments a given player has taken part in.
 * @param player_stats : the player we want to get the tournaments he was part of.
 * @return list of the tournaments a given player has taken part in.
 */
int* playerStatsGetTournaments(PlayerStats player_stats);

/**
 * PlayerStatsGetMaxGamesForTournament: get max games allowed for a given tournament.
 * @param player_stats : the player which we want to find the max games allowed for
 * one of the tournament he is part of.
 * @param tournament_id : the tournament we want to find his max games limit.
 * @return max games allowed for a given tournament.
 */
int playerStatsGetMaxGamesForTournament(PlayerStats player_stats, TournamentID tournament_id);

/**
 * playerStatsAddWin: add win to the player stats.
 * @param player_stats : the player to add the win to.
 */
void playerStatsAddWin(PlayerStats player_stats);

/**
 * playerStatsAddTie: add tie to the player stats.
 * @param player_stats : the player to add the tie to.
 */
void playerStatsAddTie(PlayerStats player_stats);

/**
 * playerStatsAddLose: add lose to the player stats.
 * @param player_stats : the player to add the lose to.
 */
void playerStatsAddLose(PlayerStats player_stats);

/**
 * playerStatsGetAmountOf: get number of wins/ loses/ ties of player.
 * @param player_stats : the player to get the number of chosen results of.
 * @param game_result : wins/ draws/ loses.
 * @return number of chosen result of player.
 */
int playerStatsGetAmountOf(PlayerStats player_stats, int game_result);

/**
 * playerStatsNullifyStats: nullify a given player's stats.
 * @param player_stats : the player to nullify his stats.
 */
void playerStatsNullifyStats(PlayerStats player_stats);

/**
 * playerStatsHasNoTournamentsCheck: check if a given players is not part of any tournament.
 * @param player_stats : the player we want to see if he is part of any tournament.
 * @return true - if the player is out of all the tournaments.
 *         false - if the player is part of one of the tournaments.
 */
bool playerStatsHasNoTournamentsCheck(PlayerStats player_stats);

/**
 * playerStatsRemoveGame: remove game from player stats and if needed also the tournament and the player itself
 * @param player_stats : the player to delete one of his games.
 * @param tournament_id : the tournament to delete one of his games.
 * @param game_id : the game to remove.
 * @return true - if we need to delete the player also.
 *         false - if we don't need to delete the player.
 */
bool playerStatsRemoveGame(PlayerStats player_stats, int tournament_id, int game_id);

#endif //MAIN_C_PLAYERSTATS_H
