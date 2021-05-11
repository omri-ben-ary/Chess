//
// Created by User on 11/05/2021.
//

/*
 * Questions:
 *      1)Shafran uses iterator in this map and we don't need it really...
 *      2) add int2str
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

void gameTableDestroy(GameTable gameTable)
{
    mapClear(gameTable);
    mapDestroy(gameTable);
}

int gameTableGetSize(GameTable gameTable)
{
    return mapGetSize(gameTable);
}

bool GameTableContains(GameTable gameTable, GameId id)
{
    return mapContains(gameTable, id);
}

GameErrorCode gameAddOrEdit(GameTable gameTable, GameId id, GameData data)
{
    return mapPut(gameTable, id, data);
}

GameData gameGet(GameTable gameTable, GameId id)
{
    return mapGet(gameTable, id);
}

GameErrorCode editGameResult(GameTable gameTable, GameId id, GameResult newResult)
{
    GameData newGameData= gameGet(gameTable, id);
    changeGameResult(newGameData, newResult);]
    gameAddOrEdit(gameTable, id, newGameData);
}


static MapKeyElement copyId(MapKeyElement id)
{
    GameId tempId = id;      //to avoid casting const pointer
    char* stringId=(char*)tempId;
    if(id == NULL)
    {
        return NULL;
    }

    char* newId = malloc(sizeof(char)*(strlen(stringId)+1));
    if(newId == NULL)
    {
        return NULL;
    }
    strcpy(newId,stringId);
    return newId;
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
    MapKeyElement id1Temp = id1;    //to avoid casting const pointer
    MapKeyElement id2Temp = id2;
    return strcmp((GameId)id1Temp,(GameId)id2Temp);
}

