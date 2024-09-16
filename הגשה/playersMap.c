#include "playersMap.h"
#include <stdlib.h>
#include <assert.h>

#define SUCCESS 1
#define REMOVED_PLAYER (-1)

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

int playersMapGetNumberOfPlayers(Players players_map)
{
    assert(players_map != NULL);
    return mapGetSize(players_map);
}
PlayerStats playersMapGetStats(Players players, PlayerID player_id)
{
    return mapGet(players, &player_id);
}

bool playersMapContain(Players players, PlayerID player_id)
{
    return mapContains(players, &player_id);
}

bool playersMapCheckForMaxGamesOfPlayer(Players players, PlayerID player_id, TournamentID tournament_id)
{
    assert(players != NULL);
    if (playersMapContain(players, player_id) == false)
    {
        return true;
    }
    return playersStatsCheckForMaxGamesOfPlayer(playersMapGetStats(players, player_id), tournament_id);
}


PlayerStatsResult playersMapAddGameStats(Players players, PlayerID player_id, int tournament_id,
                                                int game_id, int max_games_per_tournament)
{
    assert(players != NULL);
    bool player_was_just_created = false;
    if (playersMapContain(players, player_id) == false)
    {
        PlayerStats player_stats = playerStatsCreate();
        if (player_stats == NULL)
        {
            return PLAYER_STATS_OUT_OF_MEMORY;
        }
        PlayerStatsResult put_result = playersMapPut(players,player_id, player_stats);
        playerStatsDestroy(player_stats);
        if (put_result == PLAYER_STATS_OUT_OF_MEMORY)
        {
            return PLAYER_STATS_OUT_OF_MEMORY;
        }
        player_was_just_created = true;
    }
    PlayerStats player_stats = playersMapGetStats(players, player_id);
    PlayerStatsResult result = playerStatsAddGame(player_stats, tournament_id, game_id, max_games_per_tournament);
    if (result == PLAYER_STATS_OUT_OF_MEMORY )
    {
        if (player_was_just_created)
        {
            playersMapRemove(players, player_id);
        }
        return PLAYER_STATS_OUT_OF_MEMORY;
    }
    return PLAYER_STATS_GAME_ADD_SUCCESS;
}

PlayerStatsResult playersMapRemove(Players players, PlayerID player_id)
{
    assert(players != NULL);
    MapResult remove_result = mapRemove(players, &player_id);
    if (remove_result == MAP_ITEM_DOES_NOT_EXIST)
    {
        return PLAYER_STATS_NOT_EXIST;
    }
    return PLAYER_STATS_REMOVE_SUCCESS;
}

PlayerStatsResult playersMapPut(Players players, PlayerID player_id, PlayerStats player_stats)
{
    assert(players != NULL || player_stats != NULL);
    MapResult put_result = mapPut(players, &player_id, player_stats);
    if (put_result == MAP_OUT_OF_MEMORY)
    {
        return PLAYER_STATS_OUT_OF_MEMORY;
    }
    return PLAYER_STATS_PUT_SUCCESS;
}

int* playersMapGetTournaments(Players players, PlayerID player_id)
{
    assert(players != NULL);
    return playerStatsGetTournaments(playersMapGetStats(players,player_id));

}

int playersMapCalculateNumOfPlayerTournaments(const int *player_tournaments)
{
    int num_of_player_tournaments = 0;
    int k = 0;
    while (player_tournaments[k++])
    {
        num_of_player_tournaments++;
    }
    return num_of_player_tournaments;
}

int* playersMapGetGamesInTournament(Players players, PlayerID player_id, TournamentID tournament_id)
{
    assert(players != NULL);
    return playerStatsGetGamesInTournament(playersMapGetStats(players, player_id), tournament_id);
}

void playersMapRemoveTournament(Players players, PlayerID player_id, TournamentID tournament_id)
{
    assert(tournament_id > 0);
    assert(players != NULL);
    if (player_id == REMOVED_PLAYER)
    {
        return;
    }
    PlayerStats player_stats = playersMapGetStats(players, player_id);
    playerStatsRemoveTournament(player_stats, tournament_id);
}

int playersMapGetMaxGamesForTournament(Players players, PlayerID player_id, TournamentID tournament_id)
{
    assert(players != NULL);
    return playerStatsGetMaxGamesForTournament(playersMapGetStats(players,player_id),tournament_id);
}

int playersMapAddWin(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    assert(ptr_to_player_stats != NULL);
    playerStatsAddWin(ptr_to_player_stats);
    return SUCCESS;
}

int playersMapAddTie(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    assert(ptr_to_player_stats != NULL);
    playerStatsAddTie(ptr_to_player_stats);
    return SUCCESS;
}

int playersMapAddLose(Players players, PlayerID player_id)
{
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    assert(ptr_to_player_stats != NULL);
    playerStatsAddLose(ptr_to_player_stats);
    return SUCCESS;
}

int playersMapGetAmountOf(Players players, PlayerID player_id, int chosen_result)
{
    assert(players != NULL);
    return playerStatsGetAmountOf(playersMapGetStats(players, player_id), chosen_result);
}

static void playersMapNullifyStats(Players players, PlayerID player_id)
{
    assert(players != NULL);
    PlayerStats ptr_to_player_stats = playersMapGetStats(players, player_id);
    assert (ptr_to_player_stats != NULL);
    playerStatsNullifyStats(ptr_to_player_stats);
}

void PlayersMapNullifyAllPlayerStats(Players players)
{
    assert(players != NULL);
    MAP_FOREACH (int * ,player_id, players)
    {
        if (player_id == NULL)
        {
            break;
        }
        playersMapNullifyStats(players, *player_id);
        free(player_id);
    }
}

void playersMapRemoveGameFromStats(Players players, PlayerID player_id, TournamentID tournament_id, int game_id)
{
    assert(players != NULL);
    if (playerStatsRemoveGame(playersMapGetStats(players, player_id), tournament_id, game_id))
    {
        playersMapRemove(players,player_id);
    }
}






