#include "playerTournamentStats.h"
#include <stdlib.h>
#include <string.h>
#include "assert.h"

/**  returns a flag indicating whether a game is contained in the player's stats or not.
 tournament must not be NULL */
static bool playerTournamentStatsContain(PlayerTournamentStats tournament,int game_id);

struct PlayerTournamentStats_t{
    int max_games_allowed;
    int games_attended_amount;
    int *games;
};

PlayerTournamentStats playerTournamentStatsCreate(int max_games_allowed)
{
    assert(max_games_allowed > 0);
    PlayerTournamentStats tournament = malloc(sizeof(*tournament));
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

void playerTournamentStatsDestroy(PlayerTournamentStats tournament)
{
    if (tournament == NULL)
    {
        return;
    }
    free(tournament->games);
    free(tournament);
}

bool playerTournamentStatsMaxGamesCheck(PlayerTournamentStats tournament)
{
    assert(tournament != NULL);
    assert((tournament->max_games_allowed - tournament->games_attended_amount) >= 0 );
    return (tournament->max_games_allowed - tournament->games_attended_amount);
}

int playerTournamentStatsGetMaxGamesAllowed(PlayerTournamentStats tournament)
{
    assert(tournament != NULL);
    return tournament->max_games_allowed;
}

static bool playerTournamentStatsContain(PlayerTournamentStats tournament,int game_id)
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

PlayerTournamentStatsResult playerTournamentStatsAddGameStats(PlayerTournamentStats tournament, int game_id)
{
    assert(tournament != NULL);
    assert(playerTournamentStatsContain(tournament, game_id) == false);
    assert(playerTournamentStatsMaxGamesCheck(tournament) == true);
    tournament->games[tournament->games_attended_amount++] = game_id;
    return PLAYER_TOURNAMENT_STATS_GAME_ADD_SUCCESS;
}

PlayerTournamentStats playerTournamentStatsInteriorCopy(PlayerTournamentStats tournament)
{
    if (tournament == NULL)
    {
        return NULL;
    }
    PlayerTournamentStats copy_of_tournament_stats = malloc(sizeof(*copy_of_tournament_stats));
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

int* playerTournamentStatsGetGames(PlayerTournamentStats tournament)
{
    assert(tournament != NULL);
    int *list_of_games = malloc(sizeof(*list_of_games)*(tournament->max_games_allowed));
    if (list_of_games == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < tournament->max_games_allowed; i++)
    {
        list_of_games[i] = tournament->games[i];
    }
    return list_of_games;
}

PlayerTournamentStatsResult playerTournamentStatsRemoveGame(PlayerTournamentStats tournament, int game_id)
{
    assert(tournament != NULL);
    if (playerTournamentStatsContain(tournament, game_id) == false)
    {
        return PLAYER_TOURNAMENT_STATS_GAME_REMOVE_SUCCESS;
    }
    tournament->games_attended_amount--;
    int index = tournament->games_attended_amount;
    tournament->games[index] = 0;
    if (index == 0)
    {
        return PLAYER_TOURNAMENT_STATS_IS_EMPTY;
    }
    return PLAYER_TOURNAMENT_STATS_GAME_REMOVE_SUCCESS;
}