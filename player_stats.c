//TODO: THE SHIT WITH THE FREE ID OF THE MAP FOREACH

#include "player_stats.h"
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>
struct PlayerStats_t{
    int num_of_wins;
    int num_of_ties;
    int num_of_loses;
    TournamentsHistoryTable player_tournament_history_table;
};


PlayerStats playerStatsCreate()
{
    // it seems that i malloc it 2 times (one here and one in the create and i destroy the one i malloc here)
    PlayerStats player_stats = malloc(sizeof(*player_stats));
    if (player_stats == NULL)
    {
        return NULL;
    }

    // the whole mechanisem is shit!
    player_stats->player_tournament_history_table = tournamentsHistoryTableCreate();
    if (player_stats->player_tournament_history_table == NULL)
    {
        free(player_stats);
        return NULL;
    }
    player_stats->num_of_wins = 0;
    player_stats->num_of_ties = 0;
    player_stats->num_of_loses = 0;
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
    if (player_stats == NULL || player_stats->player_tournament_history_table == NULL)
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

        tournamentStatsDestroy(tournament_stats);
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

    PlayerStats copy_of_player_stats = malloc(sizeof(*copy_of_player_stats));

    if (copy_of_player_stats == NULL)
    {
        return NULL;
    }

    copy_of_player_stats->player_tournament_history_table =
            tournamentsHistoryTableCopy(player_stats->player_tournament_history_table);

    copy_of_player_stats->num_of_wins = player_stats->num_of_wins;
    copy_of_player_stats->num_of_ties = player_stats->num_of_ties;
    copy_of_player_stats->num_of_loses = player_stats->num_of_loses;
    return copy_of_player_stats;
}

void playerStatsRemoveTournament (PlayerStats player_stats, TournamentID tournament_id)
{
    tournamentHistoryRemove(player_stats->player_tournament_history_table, tournament_id); // need to check what happens if it was already deleted
}

int* playerStatsGetGamesInTournament(PlayerStats player_stats, TournamentID tournament_id)
{
    if (player_stats == NULL)
    {
        return NULL;
    }
    return tournamentGetGames(player_stats->player_tournament_history_table,tournament_id);
}

int* playerStatsGetTournaments(PlayerStats player_stats) // NEED TO REMEMBER TO FREE!!!!!
{
    if (player_stats == NULL)
    {
        return NULL;
    }
    int num_of_tournaments = 0;
    MAP_FOREACH (int * ,id, player_stats->player_tournament_history_table)
    {
        //printf("round\n");
        num_of_tournaments++;
        free(id);
    }
    //printf("num of tournaments:%d\n", num_of_tournaments);
    int* lst_of_tournaments = malloc(sizeof(*lst_of_tournaments) * (num_of_tournaments+1));
    if (lst_of_tournaments == NULL)
    {
        return NULL;
    }

    for(int i = 0; i < num_of_tournaments +1 ; i++)
    {
        lst_of_tournaments[i] = 0;
    }
    int i = 0;
    MAP_FOREACH (int * ,id, player_stats->player_tournament_history_table) //should check memory leaks
    {
        //printf("round2\n");
        //printf("element before free: %d\n",*id);
        lst_of_tournaments[i] = *id; // not sure about this line
        free(id); // not sure if it's right to free it here!
        //printf("i:%d\n",i);
        //i++;
    }
    lst_of_tournaments[num_of_tournaments] = 0;
    //printf("who is list of tournaments:%d \n", lst_of_tournaments[0]);
    return lst_of_tournaments;
}

int playerStatsGetMaxGamesForTournament(PlayerStats player_stats, TournamentID tournament_id)
{
    return tournamentStatsGetMaxGamesAllowed(
            tournamentStatsGet(player_stats->player_tournament_history_table, tournament_id));
}


void playerStatsAddWin(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    player_stats->num_of_wins++;
}

void playerStatsAddTie(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    player_stats->num_of_ties++;
}

void playerStatsAddLose(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    player_stats->num_of_loses++;
}

int playerStatsGetWins(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    return player_stats->num_of_wins;
}

int playerStatsGetTies(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    return player_stats->num_of_ties;
}

int playerStatsGetLoses(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    return player_stats->num_of_loses;
}

void playerStatsNullifyStats(PlayerStats player_stats) // very very important!!! (to nullify before getting out of the ranking function)
{
    assert(player_stats != NULL);
    player_stats->num_of_wins = 0;
    player_stats->num_of_ties = 0;
    player_stats->num_of_loses = 0;
}

