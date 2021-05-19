#ifndef EX1Q4_GAME_H
#define EX1Q4_GAME_H

#include "map.h"
#include "gamedata.h"
#include <stdbool.h>
#define PLAYER_NOT_FOUND (-1)
#define WIN_POINTS 2
#define DRAW_POINTS 1
#define STANDINGS_DATA 4
#define ID_COL 0
#define POINTS_COL 1
#define WIN_COL 2
#define LOSE_COL 3
/** Returned by 'getSize' when the received parameter is NULL */
#define UNDEFINED_SIZE (-1)

/**GameTable is a map data type**/
typedef Map GameTable;

/**Error codes that occur when using GameTable data type**/
typedef MapResult GameErrorCode;

/********************************************Functions*****************************************************/


/**
 *
 * @return
 *      NULL - if a memory allocation failed
 *      GameTable - if function succeeded
 */
GameTable gameTableCreate();

/**
 *
 * @param game_table - the game table to destroy
 */
void gameTableDestroy(GameTable game_table);

/**
 *
 * @param game_table - the game table whom size is returned
 * @return
 *      UNDEFINED_SIZE if game table is NULL
 *      otherwise returns the game table's size
 */
int gameTableGetSize(GameTable game_table);

/**
 *
 * @param game_table - the game table to search in
 * @param game_id - the game id to search for
 * @return true if the game is found and false otherwise
 */
bool gameTableContains(GameTable game_table, int game_id);

/**
 *
 * @param game_table - game table to add game to.
 * @param game_id - game key
 * @param data - game data
 * @return - Map error codes if anything failed
 */
GameErrorCode gameTableAddOrEditGame(GameTable game_table, int game_id, GameData data);

/**
 *
 * @param game_table - the game table to fetch game data from
 * @param game_id - the game id to fetch data from
 * @return
 *      NULL if the game table is NULL or the game id wasn't found
 *      otherwise return the game data
 */
GameData gameTableGetGameData(GameTable game_table, int game_id);

/**
 *
 * @param game_table - gameTable to copy
 * @return NULL if memory allocation failed or game_table is NULL
 *         otherwise returns a copy of game_table
 */
GameTable gameTableCopy(GameTable game_table);

/**
 *
 * @param game_table - game table in which the wanted game to update is found
 * @param game_id - game id
 * @param new_result - new result of the game
 */
GameErrorCode gameTableEditGameResult(GameTable game_table, int game_id, GameResult new_result);

/**
 *
 * @param game_table - game table in which the game is found
 * @param game_id - game id to modify
 * @param player_id - player id to delete
 * @return Map error codes
 */
GameErrorCode gameTableDeletePlayerInGame(GameTable game_table, int game_id, int player_id);

/**
 *
 * @param game_table - game table to sum up points
 * @param player_id_table - array of player ids
 * @param table_size - size of points_table and player_id_table
 * @param points_table - array of points corresponding to player_id_table
 * @return number of players in tournament
 */
int gameTableSumUpPoints(GameTable game_table, int** player_table, int table_size);

/**
 *
 * @param game_table - game table to search in
 * @param first_player - id of the first player
 * @param second_player - id of the second player
 * @return true if the players already met and false if not
 */
bool gameTableCheckIfPlayersMetAlready(GameTable game_table, int first_player, int second_player);


#endif //EX1Q4_GAME_H
