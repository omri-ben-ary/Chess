#include "tournamentdata.h"
#include <stdlib.h>
//#include <assert.h>
#include <string.h>

struct TournamentData_t{
    GameTable game_table;
    char* location;
    int longest_game;
    double avg_game_time;
    int max_games_per_player;
    int game_index;
    int winner_id;
    int num_of_players;
};

TournamentData tournamentDataCreate(const char* location, int max_games_per_player)
{
    TournamentData tournament_data = malloc(sizeof(*tournament_data));
    if(tournament_data == NULL)
    {
        return NULL;
    }

    tournament_data->game_table = gameTableCreate();
    if(tournament_data->game_table == NULL)
    {
        free(tournament_data);
        return NULL;
    }

    tournament_data->location = malloc(sizeof(*tournament_data->location)*(strlen(location)+1));
    if(tournament_data->location == NULL)
    {
        free(tournament_data->game_table);
        free(tournament_data);
        return NULL;
    }
    strcpy(tournament_data->location, location);
    tournament_data->max_games_per_player = max_games_per_player;
    tournament_data->longest_game = 0;
    tournament_data->avg_game_time = 0;
    tournament_data->game_index = 1;
    tournament_data->winner_id = 0;
    tournament_data->num_of_players = 0;
    return tournament_data;
}

void tournamentDataDestroy(TournamentData tournament_data)
{
    gameTableDestroy(tournament_data->game_table);
    free(tournament_data->location);
    free(tournament_data);
}

TournamentData tournamentDataCopy(TournamentData tournament_data)
{
    if(tournament_data == NULL)
    {
        return NULL;
    }

    TournamentData copy_tournament_data = malloc(sizeof(*copy_tournament_data));
    if(copy_tournament_data == NULL)
    {
        return NULL;
    }

    copy_tournament_data->game_table = gameTableCopy(tournament_data->game_table);
    if(copy_tournament_data->game_table == NULL)
    {
        free(copy_tournament_data);
        return NULL;
    }
    copy_tournament_data->location = malloc((strlen(tournament_data->location)+1)*sizeof(char));
    if(copy_tournament_data->location == NULL)
    {
        gameTableDestroy(copy_tournament_data->game_table);
        free(copy_tournament_data);
        return NULL;
    }
    strcpy(copy_tournament_data->location, tournament_data->location);
    copy_tournament_data->avg_game_time = tournament_data->avg_game_time;
    copy_tournament_data->longest_game = tournament_data->longest_game;
    copy_tournament_data->max_games_per_player = tournament_data->max_games_per_player;
    copy_tournament_data->game_index = tournament_data->game_index;
    copy_tournament_data->winner_id = tournament_data->winner_id;
    copy_tournament_data->num_of_players = tournament_data->num_of_players;
    return copy_tournament_data;
}

int tournamentDataGetLongestGame(TournamentData tournament_data)
{
    return tournament_data->longest_game;
}

void tournamentDataSetLongestGame(TournamentData tournament_data, int longest_game_time)
{
    tournament_data->longest_game = longest_game_time;
}

double tournamentDataGetAverageGameTime(TournamentData tournament_data)
{
    return tournament_data->avg_game_time;
}

void tournamentDataSetAverageGameTime(TournamentData tournament_data, int new_game_time)
{
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    int old_size = gameTableGetSize(game_table)-1;
    if(old_size == 0)
    {
        tournament_data->avg_game_time = new_game_time;
        return;
    }
    double old_avg_game_time = tournament_data->avg_game_time;
    tournament_data->avg_game_time = ((old_avg_game_time * old_size)/(old_size+1) + (double)new_game_time/(old_size+1));
}

int tournamentDataGetMaxGames(TournamentData tournament_data)
{
    return tournament_data->max_games_per_player;
}

char* tournamentDataGetLocation(TournamentData tournament_data)
{
    return tournament_data->location;
}

GameTable tournamentDataGetGameTable(TournamentData tournament_data)
{
    return tournament_data->game_table;
}

int tournamentDataGetGameIndex(TournamentData tournament_data)
{
    return tournament_data->game_index;
}

void tournamentDataIncreaseGameIndex(TournamentData tournament_data)
{
    tournament_data->game_index++;
}

int tournamentDataGetWinnerId(TournamentData tournament_data)
{
    return tournament_data->winner_id;
}

void tournamentDataSetWinnerId(TournamentData tournament_data, int winner_id)
{
    tournament_data->winner_id = winner_id;
}

int tournamentDataGetNumberOfPlayers(TournamentData tournament_data)
{
    return tournament_data->num_of_players;
}

void tournamentDataSetNumberOfPlayers(TournamentData tournament_data, int num_of_players)
{
    tournament_data->num_of_players = num_of_players;
}