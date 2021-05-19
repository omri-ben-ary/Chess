#include "game.h"
#include <assert.h>
#include <stdbool.h>
void runGameTests()
{
    GameData game1=gameDataCreate(123456,209540483,FIRST,56);
    GameData game2=gameDataCreate(43534,353452,SECOND,44);
    int game_id=3434;
    int game_id2=4544654;
    GameTable game_table = gameTableCreate();
    assert(gameTableGetSize(game_table) == 0);
    assert(gameTableAddOrEditGame(game_table,game_id,game1) == MAP_SUCCESS);
    assert(gameTableAddOrEditGame(game_table,game_id2,game2) == MAP_SUCCESS);
    assert(gameTableCheckIfPlayersMetAlready(game_table, 1, 2) == false);
    assert(gameTableCheckIfPlayersMetAlready(game_table, 123456, 209540483) == true);
    gameDataDestroy(game2);
    assert(gameTableGetSize(game_table) == 2);
    assert(gameTableContains(game_table,game_id) == true);
    assert(gameDataGetPlayer(gameTableGetGameData(game_table, game_id),PLAYER1) == 123456);
    assert(gameDataGetPlayer(gameTableGetGameData(game_table, game_id),PLAYER2) == 209540483);
    assert(gameDataGetResult(gameTableGetGameData(game_table, game_id)) == FIRST);
    assert(gameDataGetGameTime(gameTableGetGameData(game_table, game_id)) == 56);
    assert(gameTableEditGameResult(game_table,game_id,SECOND) == MAP_SUCCESS);
    assert(gameTableDeletePlayerInGame(game_table,game_id,123456) == MAP_SUCCESS);
    assert(gameTableGetGameData(game_table, game_id) != game1);
    GameTable copy_game_table = gameTableCopy(game_table);
    assert(gameDataGetPlayer(gameTableGetGameData(copy_game_table, game_id),PLAYER1) == PLAYER_NOT_FOUND);
    assert(gameDataGetPlayer(gameTableGetGameData(copy_game_table, game_id),PLAYER2) == 209540483);
    assert(gameDataGetResult(gameTableGetGameData(copy_game_table, game_id)) == SECOND);
    assert(gameDataGetGameTime(gameTableGetGameData(copy_game_table, game_id)) == 56);
    gameDataDestroy(game1);
    gameTableDestroy(game_table);
    gameTableDestroy(copy_game_table);
}

