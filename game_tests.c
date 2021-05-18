#include "game.h"
#include <assert.h>
void runGameTests()
{
    GameData game1=gameCreate(123456,209540483,FIRST,56);
    GameData game2=gameCreate(43534,353452,SECOND,44);
    int game_id=3434;
    int game_id2=4544654;
    GameTable game_table = gameTableCreate();
    assert(gameTableGetSize(game_table) == 0);
    assert(gameAddOrEdit(game_table,game_id,game1) == MAP_SUCCESS);
    assert(gameAddOrEdit(game_table,game_id2,game2) == MAP_SUCCESS);
    gameDestroy(game2);
    assert(gameTableGetSize(game_table) == 2);
    assert(gameTableContains(game_table,game_id) == true);
    assert(gameDataGetPlayer(gameGet(game_table, game_id),PLAYER1) == 123456);
    assert(gameDataGetPlayer(gameGet(game_table, game_id),PLAYER2) == 209540483);
    assert(gameDataGetResult(gameGet(game_table, game_id)) == FIRST);
    assert(gameDataGetGameTime(gameGet(game_table, game_id)) == 56);
    assert(editGameResult(game_table,game_id,SECOND) == MAP_SUCCESS);
    assert(gameDeletePlayer(game_table,game_id,123456) == MAP_SUCCESS);
    assert(gameGet(game_table, game_id) != game1);
    GameTable copy_game_table = gameTableCopy(game_table);
    assert(gameDataGetPlayer(gameGet(copy_game_table, game_id),PLAYER1) == PLAYER_NOT_FOUND);
    assert(gameDataGetPlayer(gameGet(copy_game_table, game_id),PLAYER2) == 209540483);
    assert(gameDataGetResult(gameGet(copy_game_table, game_id)) == SECOND);
    assert(gameDataGetGameTime(gameGet(copy_game_table, game_id)) == 56);
    gameDestroy(game1);
    gameTableDestroy(game_table);
    gameTableDestroy(copy_game_table);
}

