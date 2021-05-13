//
// Created by User on 11/05/2021.
//

#include "gamedata.h"
#include <string.h>
#include <stdlib.h>


GameData gameCreate(PlayerId p1, PlayerId p2, GameResult result, int game_time)
{
    if(p1 == NULL || p2 == NULL)
    {
        return NULL;
    }
    GameData game = malloc(sizeof(*game));
    if(game == NULL)
    {
        return NULL;
    }

    game->p1 = malloc((strlen(p1)+1)*sizeof(PlayerId));
    if(game->p1 == NULL)
    {
        free(game);
        return NULL;
    }
    game->p2 = malloc((strlen(p2)+1)*sizeof(PlayerId));
    if(game->p2 == NULL)
    {
        free(game->p1);
        free(game);
        return NULL;
    }
    strcpy(game->p1,p1);
    strcpy(game->p2,p2);
    game->result = result;
    game->game_time = game_time;

    return game;
}

GameData copyData(GameData src_data)
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

    copy_game->p1 = malloc((strlen((PlayerId)src_data->p1)+1)*sizeof(*copy_game->p1));
    if(copy_game->p1 == NULL)
    {
        return NULL;
    }
    copy_game->p2 = malloc((strlen((PlayerId)src_data->p2)+1)*sizeof(*copy_game->p2));
    if(copy_game->p2 == NULL)
    {
        free(copy_game->p1);
        return NULL;
    }
    strcpy(copy_game->p1,src_data->p1);
    strcpy(copy_game->p2,src_data->p2);

    copy_game->result = src_data->result;
    copy_game->game_time = src_data->game_time;
    return copy_game;
}

void gameDestroy(GameData game)
{
    if(game == NULL)
    {
        return;
    }
    free(game->p1);
    free(game->p2);
    free(game);
}

void changeGameResult(GameData game, GameResult new_result)
{
    game->result = new_result;
}