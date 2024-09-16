#ifndef EX1Q4_GAME_DATA_H
#define EX1Q4_GAME_DATA_H

#include <string.h>

#define PLAYER1 1
#define PLAYER2 2
#define DELETED_PLAYER (-1)
/**Result is an enum of all different turnouts of the game**/
typedef enum {
    FIRST,
    SECOND,
    GAME_DRAW
}GameResult;

/**value type of map**/
typedef struct GameData_t *GameData;

/**
 *
 * @param p1 - player 1 id
 * @param p2 - player 2 id
 * @param result - game result
 * @param game_time - games total time
 * @return
 */
GameData gameDataCreate(int p1, int p2, GameResult result, int game_time);

/**
 *
 * @param game - game to destroy
 */
void gameDataDestroy(GameData game);

/**
 *
 * @param src_data - variable to copy the data from
 * @return if allocation didn't work NULL
 *         otherwise pointer to copy of src_data
 */
GameData gameDataCopy(GameData src_data);

/**
 *
 * @param game - game data to change
 * @param new_result - new result to enter
 */
void gameDataChangeGameResult(GameData game, GameResult new_result);

/**
 *
 * @param game - game to modify
 * @param player_id - player to delete
 */
void gameDataDeletePlayer(GameData game, int player_id);

/**
 *
 * @param game - game to get data from
 * @param player - player 1 or 2
 * @return - player id of player 1 or 2
 */
int gameDataGetPlayer(GameData game, int player);

/**
 *
 * @param game - game to get data from
 * @return - game result enum
 */
GameResult gameDataGetResult(GameData game);

/**
 *
 * @param game - game to get data from
 * @return - game time of game
 */
int gameDataGetGameTime(GameData game);

#endif //EX1Q4_GAME_DATA_H
