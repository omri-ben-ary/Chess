//
// Created by User on 11/05/2021.
//

/*
 * Questions:

 */

#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static MapKeyElement copyGameId(MapKeyElement game_id);
static MapDataElement copyGameData(MapDataElement data);
static void freeGameId(MapKeyElement game_id);
static void freeGameData(MapKeyElement data);
static int compareGameId(MapKeyElement game_id1, MapKeyElement game_id2);
static int findPlayerIndex(int** player_table, int player_id, int table_size);

GameTable gameTableCreate()
{
    return mapCreate(copyGameData,copyGameId,freeGameData,freeGameId,compareGameId);
}

void gameTableDestroy(GameTable game_table)
{
    mapClear(game_table);
    mapDestroy(game_table);
}

int gameTableGetSize(GameTable game_table)
{
    return mapGetSize(game_table);
}

bool gameTableContains(GameTable game_table, int game_id)
{
    return mapContains(game_table, &game_id);
}

GameErrorCode gameAddOrEdit(GameTable game_table, int game_id, GameData data)
{
    return mapPut(game_table, &game_id, data);
}

GameData gameGet(GameTable game_table, int game_id)
{
    return mapGet(game_table, &game_id);
}

GameTable gameTableCopy(GameTable game_table)
{
    return mapCopy(game_table);
}

GameErrorCode editGameResult(GameTable game_table, int game_id, Winner new_result)
{
    assert(gameTableContains(game_table, game_id));
    GameData new_game_data= gameGet(game_table, game_id);
    changeGameResult(new_game_data, new_result);
    return gameAddOrEdit(game_table, game_id, new_game_data);
}

GameErrorCode gameDeletePlayer(GameTable game_table, int game_id, int player_id)
{
    assert(gameTableContains(game_table, game_id));
    GameData game_data = gameGet(game_table, game_id);
    gameDataDeletePlayer(game_data, player_id);
    return gameAddOrEdit(game_table, game_id, game_data);
}


int gameTableSumUpPoints(GameTable game_table, int** player_table, int table_size)
{
    int current_size = 0;
    MAP_FOREACH(int*, iterator, game_table) {
        assert(gameTableContains(game_table, *iterator));
        GameData game_data = gameGet(game_table, *iterator);
        int p1 = gameDataGetPlayer(game_data, PLAYER1);
        int p2 = gameDataGetPlayer(game_data, PLAYER2);
        int p1_index = findPlayerIndex(player_table, p1, table_size);
        if(p1_index == PLAYER_NOT_FOUND)
        {
            player_table[ID_COL][current_size] = p1;
            p1_index = current_size++;
        }
        int p2_index = findPlayerIndex(player_table, p2, table_size);
        if(p2_index == PLAYER_NOT_FOUND)
        {
            player_table[ID_COL][current_size] = p2;
            p2_index = current_size++;
        }
        Winner game_result = gameDataGetResult(game_data);
        if(game_result == FIRST)
        {
            player_table[POINTS_COL][p1_index] += WIN_POINTS;
            player_table[WIN_COL][p1_index]++;
            player_table[LOSE_COL][p2_index]++;
        } else if(game_result == SECOND)
        {
            player_table[POINTS_COL][p2_index] += WIN_POINTS;
            player_table[WIN_COL][p2_index]++;
            player_table[LOSE_COL][p1_index]++;
        } else {
            player_table[POINTS_COL][p1_index] += DRAW_POINTS;
            player_table[POINTS_COL][p2_index] += DRAW_POINTS;
        }
        free(iterator);
    }
    return current_size;
}

static int findPlayerIndex(int** player_table, int player_id, int table_size)
{
    int i=0;
    for (;i<table_size;i++)
    {
        if(player_table[ID_COL][i] == player_id)
        {
            return i;
        }
    }
    return PLAYER_NOT_FOUND;
}

static MapKeyElement copyGameId(MapKeyElement game_id)
{
    if(game_id == NULL)
    {
        return NULL;
    }

    int* copy_game_id = malloc(sizeof(*copy_game_id));
    if(copy_game_id == NULL)
    {
        return NULL;
    }
    *copy_game_id = *(int*)game_id;
    return copy_game_id;
}

static MapDataElement copyGameData(MapDataElement data)
{
    if(data == NULL)
    {
        return NULL;
    }
    return gameDataCopy(data);
}

static void freeGameId(MapKeyElement game_id)
{
    free(game_id);
}

static void freeGameData(MapKeyElement data)
{
    gameDestroy(data);
}

static int compareGameId(MapKeyElement game_id1, MapKeyElement game_id2)
{
    assert(game_id1 != NULL && game_id2 != NULL);
    return *(int*)game_id1-*(int*)game_id2;
}

