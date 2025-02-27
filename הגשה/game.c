#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static MapKeyElement copyGameId(MapKeyElement game_id);
static MapDataElement copyGameData(MapDataElement data);
static void freeGameId(MapKeyElement game_id);
static void freeGameData(MapKeyElement data);
static int compareGameId(MapKeyElement game_id1, MapKeyElement game_id2);
static int gameTableFindPlayerIndex(int** player_table, int player_id, int table_size);
static void gameTableCalculateGamePoints(int** player_table, GameResult game_result, int p1_index, int p2_index);

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

GameError gameTableAddOrEditGame(GameTable game_table, int game_id, GameData data)
{
    MapResult map_result = mapPut(game_table, &game_id, data);
    if(map_result == MAP_NULL_ARGUMENT)
    {
        return GAME_NULL_ARGUMENT;
    }
    if(map_result == MAP_OUT_OF_MEMORY)
    {
        return GAME_OUT_OF_MEMORY;
    }
    return GAME_SUCCESS;
}

GameData gameTableGetGameData(GameTable game_table, int game_id)
{
    return mapGet(game_table, &game_id);
}

GameTable gameTableCopy(GameTable game_table)
{
    return mapCopy(game_table);
}

GameError gameTableRemoveGame(GameTable game_table, int game_id)
{
    MapResult map_result = mapRemove(game_table, &game_id);
    if(map_result == MAP_NULL_ARGUMENT)
    {
        return GAME_NULL_ARGUMENT;
    }
    if(map_result == MAP_ITEM_DOES_NOT_EXIST)
    {
        return GAME_DOES_NOT_EXIST;
    }
    return GAME_SUCCESS;
}

GameError gameTableEditGameResult(GameTable game_table, int game_id, GameResult new_result)
{
    assert(gameTableContains(game_table, game_id));
    GameData new_game_data= gameTableGetGameData(game_table, game_id);
    gameDataChangeGameResult(new_game_data, new_result);
    return gameTableAddOrEditGame(game_table, game_id, new_game_data);

}

GameError gameTableDeletePlayerInGame(GameTable game_table, int game_id, int player_id)
{
    assert(gameTableContains(game_table, game_id));
    GameData game_data = gameTableGetGameData(game_table, game_id);
    gameDataDeletePlayer(game_data, player_id);
    return gameTableAddOrEditGame(game_table, game_id, game_data);
}


void gameTableSumUpPoints(GameTable game_table, int** player_table, int table_size)
{
    int current_size = 0;
    MAP_FOREACH(int*, iterator, game_table) {
        GameData game_data = gameTableGetGameData(game_table, *iterator);
        int p1 = gameDataGetPlayer(game_data, PLAYER1);
        int p2 = gameDataGetPlayer(game_data, PLAYER2);
        int p1_index = gameTableFindPlayerIndex(player_table, p1, table_size);
        if(p1_index == PLAYER_NOT_FOUND && p1 != DELETED_PLAYER)
        {
            player_table[ID_COL][current_size] = p1;
            p1_index = current_size++;
        }
        int p2_index = gameTableFindPlayerIndex(player_table, p2, table_size);
        if(p2_index == PLAYER_NOT_FOUND && p2 != DELETED_PLAYER)
        {
            player_table[ID_COL][current_size] = p2;
            p2_index = current_size++;
        }
        if(p1 == DELETED_PLAYER || p2 == DELETED_PLAYER)
        {
            if(p1 == DELETED_PLAYER && p2 != DELETED_PLAYER)
            {
                player_table[POINTS_COL][p2_index] += WIN_POINTS;
                player_table[WIN_COL][p2_index]++;
            }
            else if (p1 != DELETED_PLAYER)
            {
                player_table[POINTS_COL][p1_index] += WIN_POINTS;
                player_table[WIN_COL][p1_index]++;
            }
            free(iterator);
            continue;
        }
        GameResult game_result = gameDataGetResult(game_data);
        gameTableCalculateGamePoints(player_table, game_result, p1_index, p2_index);
        free(iterator);
    }
}

bool gameTableCheckIfPlayersMetAlready(GameTable game_table, int first_player, int second_player)
{
    MAP_FOREACH(int *, iterator, game_table)
    {
        if(iterator == NULL)
        {
            break;
        }
        GameData game_data = gameTableGetGameData(game_table, *iterator);
        if(gameDataGetPlayer(game_data, PLAYER1) == first_player ||
        gameDataGetPlayer(game_data, PLAYER2) == first_player)
        {
            if(gameDataGetPlayer(game_data, PLAYER1) == second_player ||
               gameDataGetPlayer(game_data, PLAYER2) == second_player)
            {
                free(iterator);
                return true;
            }
        }
        free(iterator);
    }
    return false;
}

static void gameTableCalculateGamePoints(int** player_table, GameResult game_result, int p1_index, int p2_index)
{
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
}

static int gameTableFindPlayerIndex(int** player_table, int player_id, int table_size)
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
    gameDataDestroy(data);
}

static int compareGameId(MapKeyElement game_id1, MapKeyElement game_id2)
{
    assert(game_id1 != NULL && game_id2 != NULL);
    return *(int*)game_id1-*(int*)game_id2;
}

