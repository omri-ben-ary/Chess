//
// Created by User on 11/05/2021.
//

#include "gamedata.h"
#include <string.h>
#include <stdlib.h>

struct GameData_t{
    PlayerId p1;
    PlayerId p2;
    GameResult result;
    int gameTime;
};

GameData gameCreate(PlayerId p1, PlayerId p2, GameResult result, int gameTime)
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

    game->result = result;
    game->gameTime = gameTime;

    return game;
}

GameData copyData(GameData srcData)
{
    PlayerId copyP1 = malloc((strlen((PlayerId)srcData->p1)+1)*sizeof(char));
    if(copyP1 == NULL)
    {
        return NULL;
    }
    PlayerId copyP2 = malloc((strlen((PlayerId)srcData->p2)+1)*sizeof(char));
    if(copyP1 == NULL)
    {
    return NULL;
    }
    strcpy(copyP1,srcData->p1);
    strcpy(copyP2,srcData->p2);
    return gameCreate(copyP1,copyP2,srcData->result,srcData->gameTime);
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

void changeGameResult(GameData game, GameResult newResult)
{
    game->result = newResult;
}