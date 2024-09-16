#include "playerTournamentsMap.h"
#include <stdlib.h>
#include <assert.h>


/**  returns a copy of the tournament ID.
 tournament_id must not be NULL */
static MapKeyElement copyTournamentId(MapKeyElement tournament_id);

/**  returns a copy of the tournament stats (in player's scope).
 tournament_stats must not be NULL */
static MapDataElement copyTournamentStats(MapDataElement tournament_stats);

/**  removes tournament id. */
static void freeTournamentId(MapKeyElement tournament_id);

/**  remove the tournament's stats from player's scope.*/
static void freeTournamentStats(MapKeyElement tournament_stats);

/**  returns 0 if 2 tournament IDs are equal. if they aren't it returns different number then 0.*/
static int compareTournamentIds(MapKeyElement tournament1_id, MapKeyElement tournament2_id);

/**  returns a pointer to the stats of a given tournament (inside the player's scope).
 tournaments_history_table must not be NULL */
static PlayerTournamentStats playerTournamentsHistoryTableGet(
        PlayerTournamentsHistoryTable tournaments_history_table, TournamentID tournament_id);

static MapKeyElement copyTournamentId(MapKeyElement tournament_id)
{
    if (tournament_id == NULL)
    {
        return NULL;
    }
    int *tournament_id_copy = malloc(sizeof(*tournament_id_copy));
    if (tournament_id_copy == NULL)
    {
        return NULL;
    }
    *tournament_id_copy = *(int*)tournament_id;
    return tournament_id_copy;
}

static MapDataElement copyTournamentStats(MapDataElement tournament_stats)
{
    if (tournament_stats == NULL)
    {
        return NULL;
    }
    return playerTournamentStatsInteriorCopy((PlayerTournamentStats)tournament_stats);
}

static void freeTournamentId(MapKeyElement tournament_id)
{
    free(tournament_id);
}

static void freeTournamentStats(MapKeyElement tournament_stats)
{
    playerTournamentStatsDestroy((PlayerTournamentStats)tournament_stats);
}

static int compareTournamentIds(MapKeyElement tournament1_id, MapKeyElement tournament2_id)
{
    return (*(int*)tournament1_id - *(int*)tournament2_id);
}

PlayerTournamentsHistoryTable playerTournamentsHistoryTableCreate()
{
    return mapCreate(copyTournamentStats,copyTournamentId,freeTournamentStats,freeTournamentId,compareTournamentIds);
}

void playerTournamentsHistoryTableDestroy(PlayerTournamentsHistoryTable tournaments_history_table)
{
    mapClear(tournaments_history_table);
    mapDestroy(tournaments_history_table);
}

bool playerTournamentsHistoryTableContain(PlayerTournamentsHistoryTable tournaments_history_table,
                                          TournamentID tournament_id)
{
    return mapContains(tournaments_history_table, &tournament_id);
}

void playerTournamentsHistoryTableRemove(
        PlayerTournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    assert(tournaments_history_table != NULL);
    mapRemove(tournaments_history_table, &tournament_id);

}

static PlayerTournamentStats playerTournamentsHistoryTableGet(
        PlayerTournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return mapGet(tournaments_history_table, &tournament_id);
}

PlayerTournamentStatsResult playerTournamentsHistoryTablePut(PlayerTournamentsHistoryTable tournament_history_table,
                                                             TournamentID tournament_id,
                                                             PlayerTournamentStats tournament_stats)
{
    MapResult put_result = mapPut(tournament_history_table, &tournament_id, tournament_stats);
    if (put_result == MAP_OUT_OF_MEMORY)
    {
        return PLAYER_TOURNAMENT_STATS_OUT_OF_MEMORY;
    }
    return PLAYER_TOURNAMENT_STATS_PUT_SUCCESS;
}

bool playerTournamentsHistoryTableCheckForMaxGamesOfPlayer(
        PlayerTournamentsHistoryTable player_tournament_history_table, TournamentID tournament_id)
{
    assert(player_tournament_history_table != NULL);
    return playerTournamentStatsMaxGamesCheck(playerTournamentsHistoryTableGet(
            player_tournament_history_table, tournament_id));
}

PlayerTournamentStatsResult playerTournamentsHistoryTableAddGameStats(
        PlayerTournamentsHistoryTable tournament_history_table, int tournament_id, int game_id)
{
    assert((tournament_history_table != NULL));
    return playerTournamentStatsAddGameStats(
            playerTournamentsHistoryTableGet(tournament_history_table,tournament_id), game_id);
}

PlayerTournamentsHistoryTable playerTournamentsHistoryTableCopy(
        PlayerTournamentsHistoryTable tournament_history_table)
{
    return mapCopy(tournament_history_table);
}

int* playerTournamentsHistoryTableGetGames(PlayerTournamentsHistoryTable tournaments_history_table,
                                           TournamentID tournament_id)
{
    assert(tournaments_history_table != NULL);
    return playerTournamentStatsGetGames(playerTournamentsHistoryTableGet(tournaments_history_table, tournament_id));
}

int playerTournamentsHistoryTableGetMaxGamesForTournament(PlayerTournamentsHistoryTable tournaments_history_table,
                                                          TournamentID tournament_id)
{
    assert(tournaments_history_table != NULL);
    return playerTournamentStatsGetMaxGamesAllowed(playerTournamentsHistoryTableGet(tournaments_history_table,
                                                                                    tournament_id));
}

PlayerTournamentStatsResult playerTournamentHistoryTableRemoveGame(
        PlayerTournamentsHistoryTable tournaments_history_table, int tournament_id, int game_id)
{
    assert(tournaments_history_table != NULL);
    PlayerTournamentStats tournament = playerTournamentsHistoryTableGet(tournaments_history_table, tournament_id);
    PlayerTournamentStatsResult result = playerTournamentStatsRemoveGame(tournament, game_id);
    if (result == PLAYER_TOURNAMENT_STATS_IS_EMPTY)
    {
        playerTournamentsHistoryTableRemove(tournaments_history_table,tournament_id);
    }
    return result;
}