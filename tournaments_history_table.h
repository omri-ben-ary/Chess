#ifndef MAIN_C_GAME_HISTORY_H
#define MAIN_C_GAME_HISTORY_H

#include "map.h"
#include "tournament_history.h"

typedef int TournamentID;
typedef Map TournamentsHistoryTable;

/**
* tournamentsHistoryTableCreate: Allocates a new empty tournaments history table.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new empty table in case of success.
*/
TournamentsHistoryTable  tournamentsHistoryTableCreate();

/**
* tournaments_history_table: Deallocates an existing map. Clears all elements by using the
* stored free functions.
* @param tournamentsHistoryTable - Target table to be deallocated. If table is NULL nothing will be done.
*/
void tournamentsHistoryTableDestroy(TournamentsHistoryTable tournaments_history_table);

/**
* isTournamentContained: Checks if a tournament history element already exists in the player's tournaments history.
* i.e if the player already attended in the tournament.
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
bool isTournamentContained(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id);

/**
*  TournamentHistoryRemove: Removes a specific tournament from the player's tournaments history.
*  Iterators value is undefined after this operation.
*
* @param tournaments_history_table - The table to remove the elements from.
* @param tournament_id
* 	The tournament id to find and remove his data from the table.
* 	The element will be freed using the free function given at initialization.
* 	The data element associated with this key will also be freed using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent to the function
*   MAP_ITEM_DOES_NOT_EXIST if an equal id does not already exists in the map
* 	MAP_SUCCESS the tournament id and stats had been removed successfully
*/
MapResult tournamentHistoryRemove(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id);

/**
*	TournamentStatsGet: Returns the player's tournament stats of a specific tournament.
*			            Iterator status unchanged.
* @param tournaments_history_table - The table for which to get the specific tournament's stats from.
* @param tournament_id - The id which need to be found and who's data we want to get.
* @return
*  NULL if a NULL pointer was sent or if the table does not contain any tournament with this id.
*  The tournament stats associated with the id otherwise.
*/
TournamentStats tournamentStatsGet(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id);

/**
*  TournamentStatsPut: Gives a tournament id specific stats.
*  iterators' value is undefined after this operation.
*
* @param tournaments_table - The map for which to reassign the new tournament history
* @param tournament_id - The id of the tournament which need to be reassigned
* @param tournament_stats - The the tournaments stats to associate with the given id.
*      A copy of the tournament history will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent as map or id or stats
* 	MAP_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	MAP_SUCCESS the paired elements had been inserted successfully
*/
MapResult tournamentStatsPut(TournamentsHistoryTable tournaments_table,
                             TournamentID tournament_id, TournamentStats tournament_stats);

/**
 * addGameStatsToTournamentStats: add the relevant game stats to the match tournament
 * @param tournament_history_table : the table where we want to edit one of the tournaments records
 * @param tournament_id : the id of the tournament we want to edit
 * @param game_id : the game id we want to add to the tournament stats
 * @return : TOURNAMENT_STATS_NULL_POINTER - if tournament is null.
 *           GAME_ID_IS_ALREADY_TAKEN - if game id is already exist in the array.
 *           TOURNAMENT_STATS_FULL_OF_GAMES - if the player played more games than allowed.
 *           GAME_STATS_ADD_SUCCESS - games stats were added successfully.
 */

TournamentStatsResult addGameStatsToTournamentStats(TournamentsHistoryTable tournament_history_table,
                                                    int tournament_id, int game_id);

/**
 * tournaments_history_table_copy : create a copy of a given history table.
 * @param tournament_history_table : the map to copy.
 * @return a copy of the table.
 */
TournamentsHistoryTable tournamentsHistoryTableCopy(TournamentsHistoryTable tournament_history_table);

#endif //MAIN_C_GAME_HISTORY_H