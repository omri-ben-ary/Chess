#ifndef MAIN_C_PLAYERSMAP_H
#define MAIN_C_PLAYERSMAP_H

#include "map.h"
#include "playerStats.h"

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
 * playersMapGetNumberOfPlayers: gets the number of players inside the given map.
 * @param players_map : the map to calculate the number of players inside.
 * @return number of players.
 */
int playersMapGetNumberOfPlayers(Players players_map);
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
 * playersMapCheckForMaxGamesOfPlayer: check if a given player can still play in new games in the tournament.
 * @param players : the player table that contains the player we want to check.
 * @param player_id : the player we want to check his game limit.
 * @param tournament_id : the id of the tournament we want to check if the player crossed the game limit inside.
 * @return true - if the player can play in new games.
 *         false - if the player reached the maximum game's limit.
 */
bool playersMapCheckForMaxGamesOfPlayer(Players players, PlayerID player_id, TournamentID tournament_id);

/**
 * playersMapAddGameStats: add game stats of a player to the relevant path.
 * @param players: the map of the players that contains the player we want to edit his stats.
 * @param player_id : the id of the player we want to edit his stats
 * @param tournament_id : the id of the tournament we want to edit
 * @param game_id : the game id we want to add to the tournament stats.
 * @return PLAYER_STATS_OUT_OF_MEMORY - if there was memory fail.
 *         PLAYER_STATS_GAME_ADD_SUCCESS - games stats were added successfully.
 */
PlayerStatsResult playersMapAddGameStats(Players players, PlayerID player_id, int tournament_id,
                                         int game_id, int max_games_per_tournament);

/**
*  playersMapRemove: Removes a specific player from the players map.
*  Iterators value is undefined after this operation.
* @param players - The map of players to remove the player from.
* @param player_id - The player id to find and remove his data from the map.
* @return
*   PLAYER_STATS_NOT_EXIST if an equal id does not already exists in the map
* 	PLAYER_STATS_REMOVE_SUCCESS the player id and stats had been removed successfully
*/
PlayerStatsResult playersMapRemove(Players players, PlayerID player_id);

/**
*  playersMapPut: Gives a player id specific stats.
*  iterators' value is undefined after this operation.
* @param players - The map for which to reassign the new player stats
* @param player_id - The id of the player which need to be reassigned
* @param player_stats - The player stats to associate with the given id.
*      A copy of the player stats will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	PLAYER_STATS_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	PLAYER_STATS_PUT_SUCCESS the paired elements had been inserted successfully
*/
PlayerStatsResult playersMapPut(Players players, PlayerID player_id,PlayerStats player_stats);

/**
 * playersMapGetTournaments : get games list in a specific tournament.
 * @param players :the map the contains all the players and specifically the player we want to find the tournaments
 *                  he is part of.
 * @param player_id : the id of the player we want to get the tournaments he is part of.
 * @return list of the tournaments a given player has taken part in.
 */
int* playersMapGetTournaments(Players players, PlayerID player_id);

/**
 * playersMapCalculateNumOfPlayerTournaments : count number of tournaments in a specific player tournaments array
 * @param player_tournaments : the tournaments list
 * @return num of tournaments
 */
int playersMapCalculateNumOfPlayerTournaments(const int *player_tournaments);

/**
 * playersMapGetGamesInTournament : get a list of the games a given player has taken part in a given tournament.
 * @param players : the map the contains all the players and specifically the player we want to find the games
 *                  he is part of in a given tournament.
 * @param player_id : the id of the player we want to get the games he is part of in a given tournament.
 * @param tournament_id : the id of the tournament we want to find the games the given player has taken part in.
 * @return list of the games a given player has taken player in a given tournament.
 */
int* playersMapGetGamesInTournament(Players players, PlayerID player_id, TournamentID tournament_id);

/**
 * playersMapRemoveTournament: remove a given tournament from given player stats.
 * @param players : the map of players that contains the player we want to delete a given tournament from his
 * records.
 * @param player_id : the id of the player we want to delete a given tournament from his records.
 * @param tournament_id : the id of the tournament we want to delete.
 */
void playersMapRemoveTournament(Players players, PlayerID player_id, TournamentID tournament_id);

/**
 * playersMapGetMaxGamesForTournament: get max games allowed for a given tournament.
 * @param players : map that contains the player and the tournament which we want to find his game limit.
 * @param player_id : the player which we want to find the max games allowed for one of the tournament he is
 * part of.
 * @param tournament_id : the tournament we want to find his max games limit.
 * @return max games allowed for a given tournament.

 */
int playersMapGetMaxGamesForTournament(Players players, PlayerID player_id, TournamentID tournament_id);

/**
 * playersMapAddWin:  add win to given player
 * @param players : the map of the players that contains the player we want to add a win.
 * @param player_id : the id of the player we want to add a win to.
 * @return : -1 for failure in process
 *            0 for success
 */
int playersMapAddWin(Players players, PlayerID player_id);

/**
 * playersMapAddTie:  add tie to given player
 * @param players : the map of the players that contains the player we want to add a tie.
 * @param player_id : the id of the player we want to add a tie to.
 * @return : -1 for failure in process
 *            0 for success
 */
int playersMapAddTie(Players players, PlayerID player_id);

/**
 * playersMapAddLose:  add lose to given player
 * @param players : the map of the players that contains the player we want to add a lose.
 * @param player_id : the id of the player we want to add a lose to.
 * @return : -1 for failure in process
 *            0 for success
 */
int playersMapAddLose(Players players, PlayerID player_id);

/**
 * playersMapGetAmountOf: return the amount of wins/ draws/ loses of chosen player.
 * @param players : the players map.
 * @param player_id : the id of the interesting player.
 * @param chosen_result : the result we want to get.
 * @return num of loses/ wins/ draws of the player.
 */
int playersMapGetAmountOf(Players players, PlayerID player_id, int chosen_result);

/**
 * PlayersMapNullifyAllPlayerStats: nullify number of wins, ties and loses for all of the players.
 * @param players : the map of the players.
 */
void PlayersMapNullifyAllPlayerStats(Players players);


/**
* playersMapContain: Checks if a player still exists in the players map.
* @param players - The map to search in.
* @param player_id - The element to look for.
* @return
* 	false - if one or more of the inputs is null, or if the player doesn't exist in the players' map.
* 	true - if the player appears in the players map.
*/
bool playersMapContain(Players players, PlayerID player_id);

/**
 * playersMapRemoveGameFromStats: remove game from player stats and if needed also the tournament and
 * the player itself.
 * @param players : the players map to delete the games from.
 * @param player_id : the player to delete one of his games.
 * @param tournament_id : the tournament to delete one of his games.
 * @param game_id : the game to remove.
 */
void playersMapRemoveGameFromStats(Players players, PlayerID player_id, TournamentID tournament_id, int game_id);

#endif //MAIN_C_PLAYERSMAP_H
