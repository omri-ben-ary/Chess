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
 * @param gameTable - the game table to destroy
 */
void gameTableDestroy(GameTable gameTable);

/**
 *
 * @param gameTable - the game table whom size is returned
 * @return
 *      UNDEFINED_SIZE if game table is NULL
 *      otherwise returns the game table's size
 */
int gameTableGetSize(GameTable gameTable);

/**
 *
 * @param gameTable - the game table to search in
 * @param id - the game id to search for
 * @return true if the game is found and false otherwise
 */
bool GameTableContains(GameTable gameTable, GameId id);

/**
 *
 * @param gameTable - game table to add game to.
 * @param id - game key
 * @param data - game data
 * @return - Map error codes if anything failed
 */
GameErrorCode gameAddOrEdit(GameTable gameTable, GameId id, GameData data);

/**
 *
 * @param gameTable - the game table to fetch game data from
 * @param id - the game id to fetch data from
 * @return
 *      NULL if the game table is NULL or the game id wasn't found
 *      otherwise return the game data
 */
GameData gameGet(GameTable gameTable, GameId id);

/**
 *
 * @param gameTable - game table in which the wanted game to update is found
 * @param id - game id
 * @param newResult - new result of the game
 */
GameErrorCode editGameResult(GameTable gameTable, GameId id, GameResult newResult);


#endif //EX1Q4_GAME_H
