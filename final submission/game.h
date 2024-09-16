#ifndef EX1Q4_GAME_H
#define EX1Q4_GAME_H

#include "map.h"
#include "gameData.h"
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
typedef enum GameErrorCode_t{
    GAME_NULL_ARGUMENT,
    GAME_OUT_OF_MEMORY,
    GAME_DOES_NOT_EXIST,
    GAME_SUCCESS
}GameError;

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
 * @return
 * 	GAME_NULL_ARGUMENT if a NULL was sent as map or keyElement or dataElement
 * 	GAME_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
 * 	an element or a key failed)
 * 	GAME_SUCCESS the paired elements had been inserted successfully
 */
GameError gameTableAddOrEditGame(GameTable game_table, int game_id, GameData data);

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
 * @param game_table - game table to update in
 * @param game_id - game id to remove
 * @return
 * 	GAME_NULL_ARGUMENT if a NULL was sent to the function
 *  GAME_DOES_NOT_EXIST if an equal key item does not already exists in the map
 * 	GAME_SUCCESS the paired elements had been removed successfully
 */
GameError gameTableRemoveGame(GameTable game_table, int game_id);

/**
 *
 * @param game_table - game table in which the wanted game to update is found
 * @param game_id - game id
 * @param new_result - new result of the game
 * @return
 *  GAME_NULL_ARGUMENT if a NULL was sent to the function
 *  GAME_MEMORY_ALLOCATION if a memory allocation failed
 * 	GAME_SUCCESS the paired elements had been added successfully
 */
GameError gameTableEditGameResult(GameTable game_table, int game_id, GameResult new_result);

/**
 *
 * @param game_table - game table in which the game is found
 * @param game_id - game id to modify
 * @param player_id - player id to delete
 * @return
 * 	GAME_NULL_ARGUMENT if a NULL was sent as map or keyElement or dataElement
 * 	GAME_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
 * 	an element or a key failed)
 * 	GAME_SUCCESS the paired elements had been inserted successfully
 */
GameError gameTableDeletePlayerInGame(GameTable game_table, int game_id, int player_id);

/**
 *
 * @param game_table - game table to sum up points
 * @param player_table - array of player ids, points, wins and losses
 * @param table_size - size of points_table and player_id_table
 */
void gameTableSumUpPoints(GameTable game_table, int** player_table, int table_size);

/**
 *
 * @param game_table - game table to search in
 * @param first_player - id of the first player
 * @param second_player - id of the second player
 * @return true if the players already met and false if not
 */
bool gameTableCheckIfPlayersMetAlready(GameTable game_table, int first_player, int second_player);



#endif //EX1Q4_GAME_H
