#ifndef EX1Q4_GAME_H
#define EX1Q4_GAME_H

#include "map.h"
#include "gamedata.h"
#include <stdbool.h>
/** Returned by 'getSize' when the received parameter is NULL */
#define UNDEFINED_SIZE -1

/**GameTable is a map data type**/
typedef Map GameTable;

/**GameId is a string id for each game, also key type of map**/
typedef char* GameId;

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
 * @param id - the game id to search for
 * @return true if the game is found and false otherwise
 */
bool gameTableContains(GameTable game_table, GameId id);

/**
 *
 * @param game_table - game table to add game to.
 * @param id - game key
 * @param data - game data
 * @return - Map error codes if anything failed
 */
GameErrorCode gameAddOrEdit(GameTable game_table, GameId id, GameData data);

/**
 *
 * @param game_table - the game table to fetch game data from
 * @param id - the game id to fetch data from
 * @return
 *      NULL if the game table is NULL or the game id wasn't found
 *      otherwise return the game data
 */
GameData gameGet(GameTable game_table, GameId id);

/**
 *
 * @param game_table - game table in which the wanted game to update is found
 * @param id - game id
 * @param new_result - new result of the game
 */
GameErrorCode editGameResult(GameTable game_table, GameId id, GameResult new_result);


#endif //EX1Q4_GAME_H
