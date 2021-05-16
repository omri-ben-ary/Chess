// TODO: COPY PLAYERS FUNCTION?

#ifndef MAIN_C_PLAYERS_MAP_H
#define MAIN_C_PLAYERS_MAP_H

#include "map.h"
#include "player_stats.h"

typedef int PlayerID;
typedef Map Players;

/**
* playersMapCreate: Allocates a new empty players map.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new empty map in case of success.
*/
Players playersMapCreate();

/**
* playersMapDestroy: Deallocates an existing map. Clears all elements by using the
* stored free functions.
* @param tournaments_history_table - Target table to be deallocated. If table is NULL nothing will be done.
*/
void playersMapDestroy(Players players);

/**
* playersMapGetStats: Returns the player stats.
*			         Iterator status unchanged.
* @param players - The map for which to get the specific player stats from.
* @param player_id - The id which need to be found and who's data we want to get.
* @return
*  NULL if a NULL pointer was sent or if the map does not contain any player with this id.
*  The player stats associated with the id otherwise.
*/
PlayerStats playersMapGetStats(Players players, PlayerID player_id);

/**
 * addGameStatsToPlayerStats: add game stats of a player to the relevant path.
 * @param players: the map of the players that contains the player we want to edit his stats.
 * @param player_id : the id of the player we want to edit his stats
 * @param tournament_id : the id of the tournament we want to edit
 * @param game_id : the game id we want to add to the tournament stats.
 * @return : TOURNAMENT_STATS_NULL_POINTER - if tournament is null.
 *           GAME_ID_IS_ALREADY_TAKEN - if game id is already exist in the array.
 *           TOURNAMENT_STATS_FULL_OF_GAMES - if the player played more games than allowed.
 *           GAME_STATS_ADD_SUCCESS - games stats were added successfully.
 */
TournamentStatsResult addGameStatsToPlayerStats(Players players, PlayerID player_id, int tournament_id,
                                                int game_id, int max_games_per_tournament);

/**
*  playerRemove: Removes a specific player from the players map.
*  Iterators value is undefined after this operation.
* @param players - The map of players to remove the player from.
* @param player_id - The player id to find and remove his data from the map.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent to the function
*   MAP_ITEM_DOES_NOT_EXIST if an equal id does not already exists in the map
* 	MAP_SUCCESS the player id and stats had been removed successfully
*/
MapResult playerRemove(Players players, PlayerID player_id);

/**
*  playerPut: Gives a player id specific stats.
*  iterators' value is undefined after this operation.
* @param players - The map for which to reassign the new player stats
* @param player_id - The id of the player which need to be reassigned
* @param player_stats - The player stats to associate with the given id.
*      A copy of the player stats will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent as map or id or stats
* 	MAP_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	MAP_SUCCESS the paired elements had been inserted successfully
*/
MapResult playerPut(Players players, PlayerID player_id,PlayerStats player_stats);

/**
 * playerGetTournaments :
 * @param players :the map the contains all the players and specifically the player we want to find the tournaments
 *                  he is part of.
 * @param player_id : the id of the player we want to get the tournaments he is part of.
 * @return list of the tournaments a given player has taken part in.
 */
int* playerGetTournaments(Players players, PlayerID player_id);

/**
 * playerGetGamesInTournament : get a list of the games a given player has taken part in a given tournament.
 * @param players : the map the contains all the players and specifically the player we want to find the games
 *                  he is part of in a given tournament.
 * @param player_id : the id of the player we want to get the games he is part of in a given tournament.
 * @param tournament_id : the id of the tournament we want to find the games the given player has taken part in.
 * @return list of the games a given player has taken player in a given tournament.
 */
int* playerGetGamesInTournament(Players players, PlayerID player_id, TournamentID tournament_id);

/**
 * playersRemoveTournamentFromPlayerStats: remove a given tournament from given player stats.
 * @param players : the map of players that contains the player we want to delete a given tournament from his records.
 * @param player_id : the id of the player we want to delete a given tournament from his records.
 * @param tournament_id : the id of the tournament we want to delete.
 */
void playersRemoveTournamentFromPlayerStats(Players players, PlayerID player_id, TournamentID tournament_id);

/**
 * playerGetMaxGamesForTournament: get max games allowed for a given tournament.
 * @param players : map that contains the player and the tournament which we want to find his game limit.
 * @param player_id : the player which we want to find the max games allowed for one of the tournament he is part of.
 * @param tournament_id : the tournament we want to find his max games limit.
 * @return max games allowed for a given tournament.

 */
int playerGetMaxGamesForTournament(Players players, PlayerID player_id, TournamentID tournament_id);


/**
 * playerAddWin:  add win to given player
 * @param players : the map of the players that contains the player we want to add a win.
 * @param player_id : the id of the player we want to add a win to.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerAddWin(Players players, PlayerID player_id);

/**
 * playerAddTie:  add tie to given player
 * @param players : the map of the players that contains the player we want to add a tie.
 * @param player_id : the id of the player we want to add a tie to.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerAddTie(Players players, PlayerID player_id);

/**
 * playerAddLose:  add lose to given player
 * @param players : the map of the players that contains the player we want to add a lose.
 * @param player_id : the id of the player we want to add a lose to.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerAddLose(Players players, PlayerID player_id);

/**
 * playerGetWins : get number of wins of a given player
 * @param players : the map of the players that contains the player we want to get his number of wins.
 * @param player_id : the id of the player we want to get his number of wins.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerGetWins(Players players, PlayerID player_id);

/**
 * playerGetTies : get number of ties of a given player
 * @param players : the map of the players that contains the player we want to get his number of ties.
 * @param player_id : the id of the player we want to get his number of ties.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerGetTies(Players players, PlayerID player_id);

/**
 * playerGetLoses : get number of loses of a given player
 * @param players : the map of the players that contains the player we want to get his number of loses.
 * @param player_id : the id of the player we want to get his number of loses.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerGetLoses(Players players, PlayerID player_id);

/**
 * playerNullifyStats: nullify number of wins, ties and loses of a given player.
 * @param players : the map of the players that contains the player we want to nullify his stats.
 * @param player_id : the id of the player we want to get his number of loses.
 * @return : -1 for failure in process
 *            0 for success
 */
int playerNullifyStats(Players players, PlayerID player_id);


/**
* playersContain: Checks if a player still exists in the players map.
* @param players - The map to search in.
* @param player_id - The element to look for.
* @return
* 	false - if one or more of the inputs is null, or if the player doesn't exist in the players' map.
* 	true - if the player appears in the players map.
*/
bool playersContain(Players players, PlayerID player_id);






#endif //MAIN_C_PLAYERS_MAP_H
