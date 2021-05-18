//
// Created by DELL on 11/05/2021.
//

#include "tournaments_history_table.h"
#include <stdlib.h>

static MapKeyElement copyTournamentId(MapKeyElement tournament_id);
static MapDataElement copyTournamentStats(MapDataElement tournament_stats);
static void freeTournamentId(MapKeyElement tournament_id);
static void freeTournamentStats(MapKeyElement tournament_stats);
static int compareTournamentIds(MapKeyElement tournament1_id, MapKeyElement tournament2_id);

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
    return tournamentStatsInteriorCopy((TournamentStats)tournament_stats);
}

static void freeTournamentId(MapKeyElement tournament_id)
{
    free(tournament_id);
}

static void freeTournamentStats(MapKeyElement tournament_stats)
{
    tournamentStatsDestroy((TournamentStats)tournament_stats);
}

static int compareTournamentIds(MapKeyElement tournament1_id, MapKeyElement tournament2_id)
{
    return (*(int*)tournament1_id - *(int*)tournament2_id);
}

TournamentsHistoryTable tournamentsHistoryTableCreate()
{
    return mapCreate(copyTournamentStats,copyTournamentId,freeTournamentStats,freeTournamentId,compareTournamentIds);
}

void tournamentsHistoryTableDestroy(TournamentsHistoryTable tournaments_history_table)
{
    mapClear(tournaments_history_table);
    mapDestroy(tournaments_history_table);
}

bool tournamentHistoryTableContain(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return mapContains(tournaments_history_table, &tournament_id);
}

MapResult tournamentHistoryTableRemove(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return mapRemove(tournaments_history_table, &tournament_id);
}

TournamentStats tournamentHistoryTableGet(TournamentsHistoryTable tournaments_history_table,
                                          TournamentID tournament_id)
{
    return mapGet(tournaments_history_table, &tournament_id);
}

MapResult tournamentHistoryTablePut(TournamentsHistoryTable tournament_history_table,
                             TournamentID tournament_id, TournamentStats tournament_stats)
{
    return mapPut(tournament_history_table, &tournament_id, tournament_stats);
}

TournamentStatsResult tournamentHistoryTableAddGameStats(TournamentsHistoryTable tournament_history_table,
                                                    int tournament_id, int game_id)
{
    return tournamentStatsAddGameStats(tournamentHistoryTableGet(tournament_history_table,tournament_id), game_id);
}

TournamentsHistoryTable tournamentHistoryTableCopy(TournamentsHistoryTable tournament_history_table)
{
    return mapCopy(tournament_history_table);
}

int* tournamentHistoryTableGetGames(TournamentsHistoryTable tournaments_history_table, TournamentID tournament_id)
{
    return tournamentStatsGetGames(tournamentHistoryTableGet(tournaments_history_table, tournament_id));
}

int tournamentHistoryTableGetMaxGamesForTournament(TournamentsHistoryTable tournaments_history_table,
                                                   TournamentID tournament_id)
{
    return tournamentStatsGetMaxGamesAllowed(tournamentHistoryTableGet(tournaments_history_table, tournament_id));
}