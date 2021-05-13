//
// Created by DELL on 11/05/2021.
//

#include "tournaments_history_table.h"
#include <stdlib.h>

static MapKeyElement copyTournamentId(MapKeyElement id);
static MapDataElement copyTournamentStats(MapDataElement stats);
static void freeTournamentId(MapKeyElement id);
static void freeTournamentStats(MapKeyElement stats);
static int compareTournamentIds(MapKeyElement id1, MapKeyElement id2);

static MapKeyElement copyTournamentId(MapKeyElement id)
{
    if (id == NULL)
    {
        return NULL;
    }
    int *id_copy = malloc(sizeof (*id_copy));
    if (id_copy == NULL)
    {
        return NULL;
    }
    *id_copy = *(int*)id;
    return id_copy;
}

static MapDataElement copyTournamentStats(MapDataElement stats)
{
    if (stats == NULL)
    {
        return NULL;
    }
    return tournamentStatsInteriorCopy((TournamentStats)stats);
}

static void freeTournamentId(MapKeyElement id)
{
    free(id);
}

static void freeTournamentStats(MapKeyElement stats)
{
    tournamentStatsDestroy((TournamentStats)stats);
}

static int compareTournamentIds(MapKeyElement id1, MapKeyElement id2)
{
    return (*(int*)id1 - *(int*)id2);
}

TournamentsHistoryTable tournamentsHistoryTableCreate()
{
    return mapCreate(copyTournamentStats, copyTournamentId, freeTournamentStats, freeTournamentId, compareTournamentIds);
}

void tournamentsHistoryTableDestroy(TournamentsHistoryTable tournaments_history_table)
{
    mapClear(tournaments_history_table);
    mapDestroy(tournaments_history_table);
}

bool isTournamentContained(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return mapContains(tournaments_history_table, &tournament_id);
}

MapResult tournamentHistoryRemove(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return mapRemove(tournaments_history_table, &tournament_id);
}

TournamentStats tournamentStatsGet(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return mapGet(tournaments_history_table, &tournament_id);
}

MapResult tournamentStatsPut(TournamentsHistoryTable tournaments_table,
                             TournamentID tournament_id, TournamentStats tournament_stats)
{
    return mapPut(tournaments_table, &tournament_id, tournament_stats);
}

TournamentStatsResult addGameStatsToTournamentStats(TournamentsHistoryTable tournament_history_table,
                                                    int tournament_id, int game_id)
{
    TournamentStats ptr_to_tournament_stats = tournamentStatsGet(tournament_history_table,tournament_id);
    return gameStatsAdd(ptr_to_tournament_stats, game_id);
}
