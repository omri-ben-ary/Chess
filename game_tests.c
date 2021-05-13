#include "game.h"
#include <assert.h>
void runGameTests()
{
    GameData game1=gameCreate("123456","209540483",P1_WIN,56);
    GameData game2=gameCreate("43534","353452",P2_WIN,44);
    char* game_id="3434";
    char* game_id2="4544654";
    GameTable gameTable = gameTableCreate();
    assert(gameTableGetSize(gameTable) == 0);
    assert(gameAddOrEdit(gameTable,game_id,game1) == MAP_SUCCESS);
    gameDestroy(game1);
    assert(gameAddOrEdit(gameTable,game_id2,game2) == MAP_SUCCESS);
    gameDestroy(game2);
    assert(gameTableGetSize(gameTable) == 2);
    assert(gameTableContains(gameTable,game_id) == true);
    assert(gameGet(gameTable, game_id)->game_time == 56);
    assert(editGameResult(gameTable,game_id,P2_WIN) == MAP_SUCCESS);
    assert(gameGet(gameTable, game_id)->result == P2_WIN);
    gameTableDestroy(gameTable);

}

