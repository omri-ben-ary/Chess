//
// Created by DELL on 13/05/2021.
//

#include "player_stats.h"
#include <stdlib.h>
#include <assert.h>

struct PlayerStats_t{
    TournamentsHistoryTable player_tournament_history_table;
};


PlayerStats playerStatsCreate()
{
    PlayerStats player_stats = malloc(sizeof(*player_stats));
    if (player_stats == NULL)
    {
        return NULL;
    }
    player_stats->player_tournament_history_table = tournamentsHistoryTableCreate();
    if (player_stats->player_tournament_history_table == NULL)
    {
        free(player_stats);
        return NULL;
    }
    return player_stats;
}

void playerStatsDestroy(PlayerStats player_stats)
{
    if (player_stats == NULL)
    {
        return;
    }
    tournamentsHistoryTableDestroy(player_stats->player_tournament_history_table);
    free(player_stats);
}

bool playerStatsSearchForTournament(PlayerStats player_stats, TournamentID tournament_id)
{
    assert (player_stats != NULL);
    return (isTournamentContained(player_stats->player_tournament_history_table, tournament_id));
}


TournamentStatsResult playerStatsAddGame(PlayerStats player_stats, int tournament_id,
                                         int game_id, int max_games_allowed)
{
    assert(tournament_id > 0 && game_id > 0 && max_games_allowed > 0);
    if (player_stats == NULL)
    {
        return TOURNAMENT_STATS_NULL_POINTER;
    }

    if (playerStatsSearchForTournament(player_stats, tournament_id) == false) // need to create new tournament
    {
        TournamentStats tournament_stats = tournamentStatsCreate(max_games_allowed); // should free!!!!!!!!!!!!!!!!
        if (tournament_stats == NULL)
        {
            return TOURNAMENT_STATS_OUT_OF_MEMORY;
        }
        MapResult put_result = tournamentStatsPut(player_stats->player_tournament_history_table,
                                                  tournament_id, tournament_stats);
        if (put_result == MAP_NULL_ARGUMENT)
        {
            return TOURNAMENT_STATS_NULL_POINTER;
        }
        if (put_result == MAP_OUT_OF_MEMORY)
        {
            return TOURNAMENT_STATS_OUT_OF_MEMORY;
        }
    }
    return addGameStatsToTournamentStats(player_stats->player_tournament_history_table, tournament_id, game_id);
}

PlayerStats playerStatsInteriorCopy(PlayerStats player_stats)
{
    if (player_stats == NULL)
    {
        return NULL;
    }

    PlayerStats copy_of_player_stats = playerStatsCreate();

    if (copy_of_player_stats == NULL)
    {
        return NULL;
    }

    copy_of_player_stats->player_tournament_history_table =
            tournamentsHistoryTableCopy(player_stats->player_tournament_history_table);
    return copy_of_player_stats;
}
