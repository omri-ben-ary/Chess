#include "playerStats.h"
#include <stdlib.h>
#include <assert.h>

#define WINS 0
#define TIES 2

struct PlayerStats_t{
    int num_of_wins;
    int num_of_ties;
    int num_of_loses;
    PlayerTournamentsHistoryTable player_tournament_history_table;
};

PlayerStats playerStatsCreate()
{
    PlayerStats player_stats = malloc(sizeof(*player_stats));
    if (player_stats == NULL)
    {
        return NULL;
    }
    player_stats->player_tournament_history_table = playerTournamentsHistoryTableCreate();
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
    playerTournamentsHistoryTableDestroy(player_stats->player_tournament_history_table);
    free(player_stats);
}

bool playerStatsSearchForTournament(PlayerStats player_stats, TournamentID tournament_id)
{
    assert (player_stats != NULL);
    return (playerTournamentsHistoryTableContain(player_stats->player_tournament_history_table, tournament_id));
}

bool playersStatsCheckForMaxGamesOfPlayer(PlayerStats player_stats, TournamentID tournament_id)
{
    assert(player_stats!=NULL);
    if (playerStatsSearchForTournament(player_stats, tournament_id) == false)
    {
        return true;
    }
    return playerTournamentsHistoryTableCheckForMaxGamesOfPlayer(player_stats->player_tournament_history_table,
                                                                 tournament_id);
}

PlayerStatsResult playerStatsAddGame(PlayerStats player_stats, int tournament_id,
                                     int game_id, int max_games_allowed)
{
    assert(tournament_id > 0 && game_id > 0 && max_games_allowed > 0);
    assert(player_stats != NULL && player_stats->player_tournament_history_table != NULL);
    if (playerStatsSearchForTournament(player_stats, tournament_id) == false)
    {
        PlayerTournamentStats tournament_stats = playerTournamentStatsCreate(max_games_allowed);
        if (tournament_stats == NULL)
        {
            return PLAYER_STATS_OUT_OF_MEMORY;
        }
        PlayerTournamentStatsResult put_result = playerTournamentsHistoryTablePut(
                player_stats->player_tournament_history_table, tournament_id, tournament_stats);
        playerTournamentStatsDestroy(tournament_stats);
        if (put_result == PLAYER_TOURNAMENT_STATS_OUT_OF_MEMORY)
        {
            return PLAYER_STATS_OUT_OF_MEMORY;
        }
    }
    playerTournamentsHistoryTableAddGameStats(player_stats->player_tournament_history_table, tournament_id, game_id);
    return PLAYER_STATS_GAME_ADD_SUCCESS;
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
            playerTournamentsHistoryTableCopy(player_stats->player_tournament_history_table);
    copy_of_player_stats->num_of_wins = player_stats->num_of_wins;
    copy_of_player_stats->num_of_ties = player_stats->num_of_ties;
    copy_of_player_stats->num_of_loses = player_stats->num_of_loses;
    return copy_of_player_stats;
}

void playerStatsRemoveTournament (PlayerStats player_stats, TournamentID tournament_id)
{
    assert(player_stats != NULL);
    if (playerStatsSearchForTournament(player_stats, tournament_id) == false)
    {
        return;
    }
    playerTournamentsHistoryTableRemove(player_stats->player_tournament_history_table, tournament_id);
}

int* playerStatsGetGamesInTournament(PlayerStats player_stats, TournamentID tournament_id)
{
    assert(player_stats != NULL);
    return playerTournamentsHistoryTableGetGames(player_stats->player_tournament_history_table,tournament_id);
}

int* playerStatsGetTournaments(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    int num_of_tournaments = 0;
    MAP_FOREACH (int * ,tournament_id, player_stats->player_tournament_history_table)
    {
        if (tournament_id == NULL)
        {
            break;
        }
        num_of_tournaments++;
        free(tournament_id);
    }
    int* lst_of_tournaments = malloc(sizeof(*lst_of_tournaments) * (num_of_tournaments+1));
    if (lst_of_tournaments == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < num_of_tournaments + 1 ; i++)
    {
        lst_of_tournaments[i] = 0;
    }
    int j = 0;
    MAP_FOREACH (int * ,tournament_id, player_stats->player_tournament_history_table)
    {
        if (tournament_id == NULL)
        {
            break;
        }
        lst_of_tournaments[j] = *tournament_id;
        free(tournament_id);
        j++;
    }
    return lst_of_tournaments;
}

int playerStatsGetMaxGamesForTournament(PlayerStats player_stats, TournamentID tournament_id)
{
    assert(player_stats != NULL);
    return playerTournamentsHistoryTableGetMaxGamesForTournament(
            player_stats->player_tournament_history_table,tournament_id);
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

int playerStatsGetAmountOf(PlayerStats player_stats, int game_result)
{
    assert(player_stats != NULL);
    if (game_result == WINS)
    {
        return player_stats->num_of_wins;
    }
    else if (game_result == TIES)
    {
        return player_stats->num_of_ties;
    }
    return player_stats->num_of_loses;
}

void playerStatsNullifyStats(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    player_stats->num_of_wins = 0;
    player_stats->num_of_ties = 0;
    player_stats->num_of_loses = 0;
}

bool playerStatsHasNoTournamentsCheck(PlayerStats player_stats)
{
    assert(player_stats != NULL);
    return (mapGetSize(player_stats->player_tournament_history_table) == 0);
}


bool playerStatsRemoveGame(PlayerStats player_stats, int tournament_id, int game_id)
{
    assert(player_stats != NULL);
    playerTournamentHistoryTableRemoveGame(player_stats->player_tournament_history_table, tournament_id, game_id);
    if (playerStatsHasNoTournamentsCheck(player_stats))
    {
        return true;
    }
    return false;
}
