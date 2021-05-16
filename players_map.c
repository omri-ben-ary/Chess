// TODO: COPY PLAYERS FUNCTION?

#include "players_map.h"
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>
#define FAILURE -1
#define SUCCESS 1

static MapKeyElement copyPlayerId(MapKeyElement player_id);
static MapDataElement copyPlayerStats(MapDataElement player_stats);
static void freePlayerId(MapKeyElement player_id);
static void freePlayerStats(MapKeyElement player_stats);
static int comparePlayerIds(MapKeyElement player1_id, MapKeyElement player2_id);

static MapKeyElement copyPlayerId(MapKeyElement player_id)
{
    if (player_id == NULL)
    {
        return NULL;
    }
    int *player_id_copy = malloc(sizeof(*player_id_copy));
    if (player_id_copy == NULL)
    {
        return NULL;
    }
    *player_id_copy = *(int*)player_id;
    return player_id_copy;
}

static MapDataElement copyPlayerStats(MapDataElement player_stats)
{
    if (player_stats == NULL)
    {
        return NULL;
    }
    return playerStatsInteriorCopy((PlayerStats)player_stats);
}

static void freePlayerId(MapKeyElement player_id)
{
    free(player_id);
}

static void freePlayerStats(MapKeyElement player_stats)
{
    playerStatsDestroy((PlayerStats)player_stats);
}

static int comparePlayerIds(MapKeyElement player1_id, MapKeyElement player2_id)
{
    return (*(int*)player1_id - *(int*)player2_id);
}

Players playersMapCreate()
{
    return mapCreate(copyPlayerStats,copyPlayerId, freePlayerStats, freePlayerId,comparePlayerIds);
}

void playersMapDestroy(Players players_map)
{
    mapClear(players_map);
    mapDestroy(players_map);
}

PlayerStats playersMapGetStats(Players players, PlayerID player_id)
{
    return mapGet(players, &player_id);
}

// we need this function to check if a player crossed the max allowed games limit
TournamentStatsResult addGameStatsToPlayerStats(Players players, PlayerID player_id, int tournament_id,
                                                int game_id, int max_games_per_tournament)
{
    PlayerStats player_stats = playersMapGetStats(players,player_id);
    TournamentStatsResult result = playerStatsAddGame(player_stats, tournament_id, game_id, max_games_per_tournament);
    return result;
}

// for the delete player function
MapResult playerRemove(Players players, PlayerID player_id)
{
    if (players == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    return mapRemove(players, &player_id);
}

MapResult playerPut(Players players, PlayerID player_id, PlayerStats player_stats)
{
    if (players == NULL || player_stats == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    return mapPut(players, &player_id, player_stats);
}

int* playerGetTournaments(Players players, PlayerID player_id)
{
    int* lst_of_tournaments = playerStatsGetTournaments(playersMapGetStats(players,player_id));
    return lst_of_tournaments;
}

int* playerGetGamesInTournament(Players players, PlayerID player_id, TournamentID tournament_id)
{
    return playerStatsGetGamesInTournament(playersMapGetStats(players, player_id), tournament_id);
}

void playersRemoveTournamentFromPlayerStats(Players players, PlayerID player_id, TournamentID tournament_id)
{
    assert(player_id > 0 && tournament_id > 0);
    if (players == NULL)
    {
        return;
    }
    playerStatsRemoveTournament(playersMapGetStats(players, player_id), tournament_id);
}

bool playersContain(Players players, PlayerID player_id)
{
    return mapContains(players, &player_id);
}

int playerGetMaxGamesForTournament(Players players, PlayerID player_id, TournamentID tournament_id)
{
    return playerStatsGetMaxGamesForTournament(playersMapGetStats(players,player_id),tournament_id);
}

int playerAddWin(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
        return FAILURE;
    }
    playerStatsAddWin(ptr_to_player_stats);
    return SUCCESS;
}

int playerAddTie(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
        return FAILURE;
    }
    playerStatsAddTie(ptr_to_player_stats);
    return SUCCESS;
}

int playerAddLose(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
         return FAILURE;
    }
    playerStatsAddLose(ptr_to_player_stats);
    return SUCCESS;
}

int playerGetWins(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
        return FAILURE; // TODO: check it when implementing the function
    }
    return playerStatsGetWins(ptr_to_player_stats);
}

int playerGetTies(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
        return FAILURE; // TODO: check it when implementing the function
    }
    return playerStatsGetTies(ptr_to_player_stats);
}

int playerGetLoses(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
        return FAILURE; // TODO: check it when implementing the function
    }
    return playerStatsGetLoses(ptr_to_player_stats);
}

int playerNullifyStats(Players players, PlayerID player_id) // very very important!!! (to nullify before getting out of the ranking function)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    if (ptr_to_player_stats == NULL)
    {
        return FAILURE; // TODO: check it when implementing the function
    }
    playerStatsNullifyStats(ptr_to_player_stats);
    return SUCCESS;
}







