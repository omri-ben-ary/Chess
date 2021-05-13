//
// Created by User on 11/05/2021.
//

/*
 * Questions:
 *      1)Shafran uses iterator in this map and we don't need it really...
 *      2) add int2str
 *      3)gameID needs to be in going up order
 *      4)need to add to game id a sight that game is dead
 */

#include "game.h"
#include <stdlib.h>
#include <string.h>

static MapKeyElement copyId(MapKeyElement id);
static MapDataElement copyGameData(MapDataElement data);
static void freeGameId(MapKeyElement id);
static void freeGameData(MapKeyElement data);
static int compareGameId(MapKeyElement id1, MapKeyElement id2);

GameTable gameTableCreate()
{
    return mapCreate(copyGameData,copyId,freeGameData,freeGameId,compareGameId);
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

bool gameTableContains(GameTable game_table, GameId id)
{
    return mapContains(game_table, id);
}

GameErrorCode gameAddOrEdit(GameTable game_table, GameId id, GameData data)
{
    return mapPut(game_table, id, data);
}

GameData gameGet(GameTable game_table, GameId id)
{
    return mapGet(game_table, id);
}

GameErrorCode editGameResult(GameTable game_table, GameId id, GameResult new_result)
{
    GameData new_game_data= gameGet(game_table, id);
    changeGameResult(new_game_data, new_result);
    return gameAddOrEdit(game_table, id, new_game_data);
}


static MapKeyElement copyId(MapKeyElement id)
{
    if(id == NULL)
    {
        return NULL;
    }

    GameId temp_id = id;      //to avoid casting const pointer
    char* string_id=(char*)temp_id;

    char* new_id = malloc(sizeof(char)*(strlen(string_id)+1));
    if(new_id == NULL)
    {
        return NULL;
    }
    strcpy(new_id,string_id);
    return new_id;
}

static MapDataElement copyGameData(MapDataElement data)
{
    if(data == NULL)
    {
        return NULL;
    }
    return copyData(data);
}

static void freeGameId(MapKeyElement id)
{
    free(id);
}

static void freeGameData(MapKeyElement data)
{
    gameDestroy(data);
}

static int compareGameId(MapKeyElement id1, MapKeyElement id2)
{
    MapKeyElement id1_temp = id1;    //to avoid casting const pointer
    MapKeyElement id2_temp = id2;
    return strcmp((GameId)id1_temp,(GameId)id2_temp);
}

