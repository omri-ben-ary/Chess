//
// Created by User on 13/05/2021.
//

#include "tournament.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PLAYERS_PER_GAME 2

static MapDataElement copy_tournament_data(MapDataElement tournament_data);
static MapKeyElement copy_tournament_id(MapKeyElement tournament_id);
static void free_tournament_data(MapDataElement tournament_data);
static void free_tournament_id(MapKeyElement tournament_id);
static int compare_tournament_id(MapKeyElement tournament_id1, MapKeyElement tournament_id2);
static int tournamentFindWinner(int** player_table, int game_table_size);

TournamentTable tournamentTableCreate()
{
    return mapCreate(copy_tournament_data,copy_tournament_id,free_tournament_data,free_tournament_id,
                     compare_tournament_id);
}

void tournamentTableDestroy(TournamentTable tournament_table)
{
    mapClear(tournament_table);
    mapDestroy(tournament_table);
}

bool tournamentTableContains(TournamentTable tournament_table, TournamentId tournament_id)
{
    return mapContains(tournament_table, &tournament_id);
}

TournamentErrorCode tournamentAddOrEdit(TournamentTable tournament_table, TournamentId tournament_id,
                                        TournamentData tournament_data)
{
    return mapPut(tournament_table, &tournament_id, tournament_data);
}

TournamentData tournamentTableGetData(TournamentTable tournament_table, TournamentId tournament_id)
{
    return mapGet(tournament_table, &tournament_id);
}

TournamentErrorCode tournamentDelete(TournamentTable tournament_table, TournamentId tournament_id)
{
    return mapRemove(tournament_table,&tournament_id);
}

TournamentErrorCode tournamentTableAddGame(TournamentTable tournament_table, TournamentId tournament_id,
                                           int first_player, int second_player, GameResult winner, int play_time)
{
    GameData game_data = gameCreate(first_player,second_player,winner,play_time);
    if(game_data == NULL)
    {
        return MAP_OUT_OF_MEMORY;
    }
    TournamentData tournament_data = tournamentTableGetData(tournament_table, tournament_id);
    assert(tournament_data != NULL);
    if(play_time > tournamentDataGetLongestGame(tournament_data))
    {
        tournamentDataSetLongestGame(tournament_data, play_time);
    }
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(game_table != NULL);
    int game_id = tournamentDataGetGameIndex(tournament_data);
    TournamentErrorCode error_code = gameAddOrEdit(game_table, game_id, game_data);
    tournamentDataSetAverageGameTime(tournament_data, play_time);
    gameDestroy(game_data);
    return error_code;
}

TournamentErrorCode tournamentGameRemovePlayer(TournamentTable tournament_table, TournamentId tournament_id, int game_id,
                                     int player_id)
{
    TournamentData tournament_data = tournamentTableGetData(tournament_table, tournament_id);
    assert(tournament_data != NULL);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(game_table != NULL);
    assert(gameTableContains(game_table, game_id));
    GameData game_data = gameGet(game_table, game_id);
    if(player_id == gameDataGetPlayer(game_data, PLAYER1))
    {
        if(gameDataGetResult(game_data) == FIRST || gameDataGetResult(game_data) == GAME_DRAW)
        {
            editGameResult(game_table, game_id, SECOND);
        }
    } else {
        if(gameDataGetResult(game_data) == SECOND || gameDataGetResult(game_data) == GAME_DRAW)
        {
            editGameResult(game_table, game_id, FIRST);
        }
    }
    return gameDeletePlayer(game_table, game_id, player_id);
}

TournamentErrorCode tournamentEnd(TournamentTable tournament_table, TournamentId tournament_id, int* winner_id,
                                  int* num_of_players)
{
    TournamentData tournament_data = tournamentTableGetData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    int game_table_size = PLAYERS_PER_GAME * gameTableGetSize(game_table);
    int* player_table [STANDINGS_DATA];
    for(int i=0; i<STANDINGS_DATA; i++)
    {
        player_table[i] = malloc(game_table_size*sizeof(*player_table));
        if(player_table[i] == NULL)
        {
            return MAP_OUT_OF_MEMORY;
        }
    }
    for(int i=0; i<game_table_size; i++)
    {
        for(int j=0; j<STANDINGS_DATA; j++)
        {
            player_table[j][i] = 0;
        }
    }
    *num_of_players = gameTableSumUpPoints(game_table, player_table, game_table_size);
    *winner_id = tournamentFindWinner(player_table, game_table_size);
    for(int i=0; i<STANDINGS_DATA; i++)
    {
        free(player_table[i]);
    }
    return MAP_SUCCESS;
}

TournamentErrorCode tournamentGetStats(TournamentTable tournament_table, TournamentId tournament_id, char* path_file,
                                       int winner, int num_of_players)
{
    FILE* tournament_stats = fopen(path_file, "w"); //name check
    if(tournament_stats == NULL)
    {
        return MAP_OUT_OF_MEMORY;
    }
    TournamentData tournament_data = tournamentTableGetData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    int tournament_num_of_games = gameTableGetSize(game_table);
    assert(tournament_num_of_games != UNDEFINED_SIZE);
    fprintf(tournament_stats,"%d\n",winner);
    fprintf(tournament_stats, "%d\n", tournamentDataGetLongestGame(tournament_data));
    fprintf(tournament_stats, "%lf\n", tournamentDataGetAverageGameTime(tournament_data));
    fprintf(tournament_stats, "%s\n", tournamentDataGetLocation(tournament_data));
    fprintf(tournament_stats, "%d\n", tournament_num_of_games);
    fprintf(tournament_stats, "%d\n", num_of_players);

    fclose(tournament_stats);
    return MAP_SUCCESS;
}

int tournamentGetGameTime(TournamentTable tournament_table, TournamentId tournament_id, int game_id)
{
    TournamentData tournament_data = tournamentTableGetData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(gameTableContains(game_table, game_id));
    GameData  game_data = gameGet(game_table,game_id);
    return gameDataGetGameTime(game_data);
}

int tournamentGetPlayerResult(TournamentTable tournament_table, TournamentId tournament_id, int game_id,
                              int player_id)
{
    TournamentData tournament_data = tournamentTableGetData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(gameTableContains(game_table, game_id));
    GameData game_data = gameGet(game_table, game_id);
    GameResult result = gameDataGetResult(game_data);
    if(result == GAME_DRAW)
    {
        return PLAYER_DRAW;
    }
    int p1 = gameDataGetPlayer(game_data, PLAYER1);
    if(player_id == p1)
    {
        if(result == FIRST)
        {
            return PLAYER_WIN;
        } else{
            return PLAYER_LOSE;
        }
    }else{
        if(result == SECOND)
        {
            return PLAYER_WIN;
        } else{
            return PLAYER_LOSE;
        }
    }
}

int tournamentTableGetNumberOfGames(TournamentTable tournament_table)
{
    int games = 0;
    MAP_FOREACH(int *, iterator, tournament_table){
        TournamentData tournament_data = tournamentTableGetData(tournament_table, *iterator);
        GameTable game_table = tournamentDataGetGameTable(tournament_data);
        int games_in_tournament = gameTableGetSize(game_table);
        assert(games_in_tournament != UNDEFINED_SIZE);
        games += games_in_tournament;
        free(iterator);
    }
    return games;
}

static int tournamentFindWinner(int** player_table, int game_table_size)
{
    int max_points = 0;
    for(int i=0; i<game_table_size; i++)
    {
        if(player_table[POINTS_COL][i] > max_points)
        {
            max_points = player_table[POINTS_COL][i];
        }
    }
    int max_wins = 0, min_lose = MIN_LOSE_INIT, winner_id = 0;
    for(int i=0; i<game_table_size;i++)
    {
        if(player_table[POINTS_COL][i] == max_points)
        {
            if(min_lose == MIN_LOSE_INIT || player_table[LOSE_COL][i] < min_lose)
            {
                min_lose = player_table[LOSE_COL][i];
                max_wins = player_table[WIN_COL][i];
                winner_id = player_table[ID_COL][i];
            } else if(player_table[LOSE_COL][i] == min_lose)
            {
                if(player_table[WIN_COL][i] > max_wins)
                {
                    max_wins = player_table[WIN_COL][i];
                    winner_id = player_table[ID_COL][i];
                } else if(player_table[WIN_COL][i] == max_wins)
                {
                    if(player_table[ID_COL][i] < winner_id)
                    {
                        winner_id = player_table[ID_COL][i];
                    }
                }
            }
        }
    }
    return winner_id;
}
static MapDataElement copy_tournament_data(MapDataElement tournament_data)
{
    if(tournament_data == NULL)
    {
        return NULL;
    }

    return tournamentDataCopy(tournament_data);
}

static MapKeyElement copy_tournament_id(MapKeyElement tournament_id)
{
    if(tournament_id == NULL)
    {
        return NULL;
    }
    int* copy_id = malloc(sizeof(*copy_id));
    if(copy_id == NULL)
    {
        return NULL;
    }
    *copy_id = *(int*)tournament_id;
    return copy_id;
}

static void free_tournament_data(MapDataElement tournament_data)
{
    if(tournament_data == NULL)
    {
        return;
    }
    tournamentDataDestroy(tournament_data);
}

static void free_tournament_id(MapKeyElement tournament_id)
{
    free(tournament_id);
}

static int compare_tournament_id(MapKeyElement tournament_id1, MapKeyElement tournament_id2)
{
    assert(tournament_id1 != NULL && tournament_id2 != NULL);
    return *(int*)tournament_id1 - *(int*)tournament_id2;
}