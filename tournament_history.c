// who should kill the copy?

#include "tournament_history.h"
#include <stdlib.h>
#include <string.h>
#include "assert.h"

struct TournamentStats_t{
    int max_games_allowed;
    int games_attended_amount;
    int *games;
};

TournamentStats tournamentStatsCreate(int max_games_allowed)
{
    if (max_games_allowed <= 0)
    {
        return NULL;
    }
    TournamentStats tournament = malloc(sizeof (*tournament));
    if (tournament == NULL)
    {
        return NULL;
    }
    tournament->games = malloc(sizeof(tournament->games) * max_games_allowed);
    if (tournament->games == NULL)
    {
        free(tournament);
        return NULL;
    }
    for (int i = 0 ; i < max_games_allowed ; i++)
    {
        tournament->games[i] = 0;
    }
    tournament->max_games_allowed = max_games_allowed;
    tournament->games_attended_amount = 0;
    return tournament;
}

// notice that there arent any defence implemented here
bool playerPlayedMaxGamesCheck(TournamentStats tournament)
{
    assert((tournament->max_games_allowed - tournament->games_attended_amount) >= 0 );
    return (tournament->max_games_allowed - tournament->games_attended_amount);
}

int maxGamesAllowedGet(TournamentStats tournament)
{
    return tournament->max_games_allowed;
}

bool gameStatsContainedCheck(TournamentStats tournament,int game_id)
{
    assert (tournament != NULL);
    for (int i = 0 ; i < tournament->games_attended_amount ; i++)
    {
        if (tournament->games[i] == game_id)
        {
            return true;
        }
    }
    return false;
}

TournamentStatsResult gameStatsAdd(TournamentStats tournament, int game_id)
{
    if (tournament == NULL)
    {
        return TOURNAMENT_STATS_NULL_POINTER;
    }
    if (gameStatsContainedCheck(tournament, game_id))
    {
        return GAME_ID_IS_ALREADY_TAKEN;
    }
    if (playerPlayedMaxGamesCheck(tournament))
    {
        return TOURNAMENT_STATS_FULL_OF_GAMES;
    }
    tournament->games[tournament->games_attended_amount++] = game_id;
    return GAME_STATS_ADD_SUCCESS;
}

void tournamentStatsDestroy(TournamentStats tournament)
{
    if (tournament == NULL)
    {
        return;
    }
    free(tournament->games);
    free(tournament);
}

TournamentStats tournamentStatsInteriorCopy(TournamentStats tournament)
{
    if (tournament == NULL)
    {
        return NULL;
    }

    TournamentStats copy_of_tournament_stats = malloc(sizeof(*copy_of_tournament_stats));
    if (copy_of_tournament_stats == NULL)
    {
        return NULL;
    }
    int length = tournament->max_games_allowed;
    copy_of_tournament_stats->games = malloc(sizeof(*(copy_of_tournament_stats->games))* length);
    memcpy(copy_of_tournament_stats->games, tournament->games,
           sizeof (*(copy_of_tournament_stats->games)) * length);
    if (copy_of_tournament_stats->games == NULL)
    {
        free(copy_of_tournament_stats);
        return NULL;
    }
    copy_of_tournament_stats->max_games_allowed = tournament->max_games_allowed;
    copy_of_tournament_stats->games_attended_amount = tournament->games_attended_amount;
    return copy_of_tournament_stats;
}

