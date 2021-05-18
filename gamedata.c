#include "gamedata.h"
#include <string.h>
#include <stdlib.h>
#define DELETED_PLAYER (-1)

struct GameData_t{
    int p1;
    int p2;
    GameResult result;
    int game_time;
};


GameData gameDataCreate(int p1, int p2, GameResult result, int game_time)
{

    GameData game = malloc(sizeof(*game));
    if(game == NULL)
    {
        return NULL;
    }

    game->p1 = p1;
    game->p2 = p2;
    game->result = result;
    game->game_time = game_time;

    return game;
}

GameData gameDataCopy(GameData src_data)
{
    if(src_data == NULL)
    {
        return NULL;
    }

    GameData copy_game = malloc(sizeof(*copy_game));
    if(copy_game == NULL)
    {
        return NULL;
    }

    copy_game->p1 = src_data->p1;
    copy_game->p2 = src_data->p2;
    copy_game->result = src_data->result;
    copy_game->game_time = src_data->game_time;
    return copy_game;
}

void gameDataDestroy(GameData game)
{
    if(game == NULL)
    {
        return;
    }
    free(game);
}

void gameDataChangeGameResult(GameData game, GameResult new_result)
{
    game->result = new_result;
}

void gameDataDeletePlayer(GameData game, int player_id)
{
    if(game->p1 == player_id)
    {
        game->p1 = DELETED_PLAYER;
    } else{
        game->p2 = DELETED_PLAYER;
    }
}

int gameDataGetPlayer(GameData game, int player)
{
    if(player == PLAYER1)
    {
        return game->p1;
    }
    return game->p2;
}

GameResult gameDataGetResult(GameData game)
{
    return game->result;
}

int gameDataGetGameTime(GameData game)
{
    return game->game_time;
}