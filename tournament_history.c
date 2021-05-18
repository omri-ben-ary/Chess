// who should kill the copy?

#include "tournament_history.h"
#include <stdlib.h>
#include <string.h>
#include "assert.h"

#define FAILURE (-1)

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
    TournamentStats tournament = malloc(sizeof(*tournament));
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

bool tournamentStatsMaxGamesCheck(TournamentStats tournament)
{
    assert(tournament != NULL);
    assert((tournament->max_games_allowed - tournament->games_attended_amount) >= 0 );
    return (tournament->max_games_allowed - tournament->games_attended_amount);
}

int tournamentStatsGetMaxGamesAllowed(TournamentStats tournament)
{
    if (tournament == NULL)
    {
        return FAILURE;
    }
    return tournament->max_games_allowed;
}

bool tournamentStatsContain(TournamentStats tournament,int game_id)
{
    assert (tournament != NULL && game_id > 0);
    for (int i = 0 ; i < tournament->games_attended_amount ; i++)
    {
        if (tournament->games[i] == game_id)
        {
            return true;
        }
    }
    return false;
}

TournamentStatsResult tournamentStatsAddGameStats(TournamentStats tournament, int game_id)
{
    if (tournament == NULL)
    {
        return TOURNAMENT_STATS_NULL_POINTER;
    }
    if (game_id <= 0)
    {
        return INVALID_GAME_ID;
    }
    if (tournamentStatsContain(tournament, game_id))
    {
        return GAME_ID_IS_ALREADY_TAKEN;
    }
    if (!(tournamentStatsMaxGamesCheck(tournament)))
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

int* tournamentStatsGetGames(TournamentStats tournament)
{
    if (tournament == NULL)
    {
        return NULL;
    }
    int *list_of_games = malloc(sizeof(*list_of_games)*(tournament->max_games_allowed));
    if (list_of_games == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < tournament->max_games_allowed; i++) // the rest of the array will be zeroes
    {
        list_of_games[i] = tournament->games[i];
    }
    return list_of_games;
}
