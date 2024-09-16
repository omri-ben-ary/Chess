#ifndef MAIN_C_GAME_HISTORY_H
#define MAIN_C_GAME_HISTORY_H

#include "map.h"
#include "playerTournamentStats.h"

typedef int TournamentID;
typedef Map PlayerTournamentsHistoryTable;

/**
* playerTournamentsHistoryTableCreate: Allocates a new empty tournaments history table.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new empty table in case of success.
*/
PlayerTournamentsHistoryTable playerTournamentsHistoryTableCreate();

/**
* playerTournamentsHistoryTableDestroy: Deallocates an existing map. Clears all elements by using the
* stored free functions.
* @param tournaments_history_table - Target table to be deallocated. If table is NULL nothing will be done.
*/
void playerTournamentsHistoryTableDestroy(PlayerTournamentsHistoryTable tournaments_history_table);

/**
* playerTournamentsHistoryTableContain: Checks if a tournament history element already exists in the player's
* tournaments history. i.e if the player already attended in the tournament.
* The tournament element will be considered in the player's tournaments history
* if one of the tournament id's in the table is determined equal
* using the comparison function used to initialize the tournaments history table.
*
* @param tournaments_history_table - The table to search in.
* @param tournament_id - The element to look for.
* @return
* 	false - if one or more of the inputs is null, or if the player hasn't taken place in the tournament before.
* 	true - if the player has already taken place in at least one game in the tournament before.
*/
bool playerTournamentsHistoryTableContain(PlayerTournamentsHistoryTable tournaments_history_table,
                                          TournamentID tournament_id);

/**
*  TournamentHistoryRemove: Removes a specific tournament from the player's tournaments history.
*  Iterators value is undefined after this operation.
*
* @param playerTournamentsHistoryTableRemove - The table to remove the elements from.
* @param tournament_id
* 	The tournament id to find and remove his data from the table.
* 	The element will be freed using the free function given at initialization.
* 	The data element associated with this key will also be freed using the free function given at initialization.
*/
void playerTournamentsHistoryTableRemove(PlayerTournamentsHistoryTable tournaments_history_table,
                                         TournamentID tournament_id);

/**
*  playerTournamentsHistoryTablePut: Gives a tournament id specific stats.
*  iterators' value is undefined after this operation.
*
* @param tournament_history_table - The map for which to reassign the new tournament history
* @param tournament_id - The id of the tournament which need to be reassigned
* @param tournament_stats - The tournaments stats to associate with the given id.
*      A copy of the tournament history will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	PLAYER_TOURNAMENT_STATS_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	PLAYER_TOURNAMENT_STATS_PUT_SUCCESS the paired elements had been inserted successfully
*/
PlayerTournamentStatsResult playerTournamentsHistoryTablePut(PlayerTournamentsHistoryTable tournament_history_table,
                                                             TournamentID tournament_id,
                                                             PlayerTournamentStats tournament_stats);

/**
 * playerTournamentsHistoryTableCheckForMaxGamesOfPlayer: check if there is still space for new games in
 * a given tournament.
 * @param player_tournament_history_table : the tournament history of the player we want to check his game limit.
 * @param tournament_id : the id of the tournament we want to check if the player crossed the game limit inside.
 * @return true - if the player can play in new games.
 *         false - if the player reached the maximum game's limit.
 */
bool playerTournamentsHistoryTableCheckForMaxGamesOfPlayer(
        PlayerTournamentsHistoryTable player_tournament_history_table, TournamentID tournament_id);

/**
 * playerTournamentsHistoryTableAddGameStats: add the relevant game stats to the match tournament
 * @param tournament_history_table : the table where we want to edit one of the tournaments records
 * @param tournament_id : the id of the tournament we want to edit
 * @param game_id : the game id we want to add to the tournament stats
 * @return : GAME_STATS_ADD_SUCCESS - games stats were added successfully.
 */
PlayerTournamentStatsResult playerTournamentsHistoryTableAddGameStats(
        PlayerTournamentsHistoryTable tournament_history_table, int tournament_id, int game_id);

/**
 * playerTournamentsHistoryTableCopy : create a copy of a given history table.
 * @param tournament_history_table : the map to copy.
 * @return a copy of the table.
 */
PlayerTournamentsHistoryTable playerTournamentsHistoryTableCopy(
        PlayerTournamentsHistoryTable tournament_history_table);

/**
 * playerTournamentsHistoryTableGetGames: create a list of the games that a given player played in a
 * given tournament.
 * @param tournaments_history_table : the map that contains all of the tournaments that a player was taking part it,
 * and specifically the tournament which we want to get the games the player was taking part in.
 * @param tournament_id : the id of the tournament we want to get the list of games that the player was taking
 * part in.
 * @return a list of the games that a player played in a given tournament
 */
int* playerTournamentsHistoryTableGetGames(PlayerTournamentsHistoryTable tournaments_history_table,
                                           TournamentID tournament_id);

/**
 * playerTournamentsHistoryTableGetMaxGamesForTournament : get max games allowed for a given tournament.
 * @param tournaments_history_table : the map of tournaments.
 * @param tournament_id : the id of the wanted tournament.
 * @return max games allowed for tournament.
 */
int playerTournamentsHistoryTableGetMaxGamesForTournament(PlayerTournamentsHistoryTable tournaments_history_table,
                                                          TournamentID tournament_id);

/**
 * playerTournamentHistoryTableRemoveGame: remove game from a given tournament table and
 * deletes the tournament if needed.
 * @param tournaments_history_table : the table to remove the game from.
 * @param tournament_id : the tournament id to remove the game from.
 * @param game_id : the game to remove.
 * @return PLAYER_TOURNAMENT_STATS_IS_EMPTY : if it's the only game in the tournament.
 *         PLAYER_TOURNAMENT_STATS_GAME_REMOVE_SUCCESS : if everything succeeded.
 */
PlayerTournamentStatsResult playerTournamentHistoryTableRemoveGame(
        PlayerTournamentsHistoryTable tournaments_history_table, int tournament_id, int game_id);
#endif //MAIN_C_GAME_HISTORY_H