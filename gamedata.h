#ifndef EX1Q4_GAME_DATA_H
#define EX1Q4_GAME_DATA_H

#include <string.h>


/**PlayerId is string id for each player in game**/
typedef char* PlayerId;

/**Result is an enum of all different turnouts of the game**/
typedef enum {
    P1_WIN,
    P2_WIN,
    TIE
}GameResult;

/**value type of map**/
typedef struct GameData_t *GameData;

/**
 *
 * @param p1 - player 1 id
 * @param p2 - player 2 id
 * @param result - game result
 * @param gameTime - games total time
 * @return
 */
GameData gameCreate(PlayerId p1, PlayerId p2, GameResult result, int gameTime);

/**
 *
 * @param game - game to destroy
 */
void gameDestroy(GameData game);

/**
 *
 * @param srcData - variable to copy the data from
 * @return if allocation didn't work NULL
 *         otherwise pointer to copy of srcData
 */
GameData copyData(GameData srcData);

/**
 *
 * @param game - game data to change
 * @param newResult - new result to enter
 */
void changeGameResult(GameData game, GameResult newResult);

#endif //EX1Q4_GAME_DATA_H
