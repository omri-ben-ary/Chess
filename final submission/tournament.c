#include "tournament.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PLAYERS_PER_GAME 2
/** copy function of touranment id for map **/
static MapDataElement copyTournamentData(MapDataElement tournament_data);

/** copy function of touranment data for map **/
static MapKeyElement copyTournamentId(MapKeyElement tournament_id);

/** free function of tournament id for map**/
static void freeTournamentData(MapDataElement tournament_data);

/** free function of tournament data for map**/
static void freeTournamentId(MapKeyElement tournament_id);

/** compare tournament id function for map**/
static int compareTournamentId(MapKeyElement tournament_id1, MapKeyElement tournament_id2);

/** used in tournamentEnd after all points wins and losses were updated to player_table
  the function returns the winner id**/
static int tournamentTableFindWinnerInTournament(int** player_table, int player_table_size);

/** every time a game is added to the tournament table thid function check if new players
 * were added to the table and updates it accordingly**/
static int tournamentTableUpdatePlayerCount(TournamentData tournament_data, int player_id);

/** used in tournamentTableGetStats to print out the results**/
static TournamentError tournamentTablePrintStats(FILE* tournament_stats, TournamentData tournament_data,
                                                 int tournament_num_of_games);

TournamentTable tournamentTableCreate()
{
    return mapCreate(copyTournamentData,copyTournamentId,freeTournamentData,freeTournamentId,
                     compareTournamentId);
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

TournamentError tournamentTableAddOrEditTournament(TournamentTable tournament_table, TournamentId tournament_id,
                                        TournamentData tournament_data)
{
    MapResult map_result = mapPut(tournament_table, &tournament_id, tournament_data);
    if (map_result == MAP_NULL_ARGUMENT)
    {
        return TOURNAMENT_NULL_ARGUMENT;
    }
    if (map_result == MAP_OUT_OF_MEMORY)
    {
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    return TOURNAMENT_SUCCESS;
}

TournamentData tournamentTableGetTournamentData(TournamentTable tournament_table, TournamentId tournament_id)
{
    return mapGet(tournament_table, &tournament_id);
}

TournamentError tournamentTableDeleteTournament(TournamentTable tournament_table, TournamentId tournament_id)
{
    MapResult map_result = mapRemove(tournament_table,&tournament_id);
    if (map_result == MAP_NULL_ARGUMENT)
    {
        return TOURNAMENT_NULL_ARGUMENT;
    }
    if (map_result == MAP_ITEM_DOES_NOT_EXIST)
    {
        return TOURNAMENT_DOES_NOT_EXIST;
    }
    return TOURNAMENT_SUCCESS;
}


TournamentError tournamentTableAddGame(TournamentTable tournament_table, TournamentId tournament_id,
                                           int first_player, int second_player, GameResult winner, int play_time,
                                           int* num_of_players_added)
{
    TournamentData tournament_data = tournamentTableGetTournamentData(tournament_table, tournament_id);
    assert(tournament_data != NULL);
    GameData game_data = gameDataCreate(first_player,second_player,winner,play_time);
    if (game_data == NULL)
    {
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    if (play_time > tournamentDataGetLongestGame(tournament_data))
    {
        tournamentDataSetLongestGame(tournament_data, play_time);
    }
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(game_table != NULL);
    int game_id = tournamentDataGetGameIndex(tournament_data);
    tournamentDataIncreaseGameIndex(tournament_data);
    *num_of_players_added += tournamentTableUpdatePlayerCount(tournament_data,first_player);
    *num_of_players_added += tournamentTableUpdatePlayerCount(tournament_data,second_player);
    GameError error_code = gameTableAddOrEditGame(game_table, game_id, game_data);
    gameDataDestroy(game_data);
    if (error_code == GAME_NULL_ARGUMENT)
    {
        tournamentDataSetNumberOfPlayers(
                tournament_data,tournamentDataGetNumberOfPlayers(tournament_data)-*num_of_players_added);
        return TOURNAMENT_NULL_ARGUMENT;
    }
    if (error_code == GAME_OUT_OF_MEMORY)
    {
        tournamentDataSetNumberOfPlayers(
                tournament_data,tournamentDataGetNumberOfPlayers(tournament_data)-*num_of_players_added);
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    tournamentDataSetAverageGameTime(tournament_data, play_time);
    return TOURNAMENT_SUCCESS;
}

TournamentError tournamentTableRemovePlayerInGame(TournamentTable tournament_table, TournamentId tournament_id,
                                                      int game_id,int player_id)
{
    TournamentData tournament_data = tournamentTableGetTournamentData(tournament_table, tournament_id);
    assert(tournament_data != NULL);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(game_table != NULL);
    assert(gameTableContains(game_table, game_id));
    GameData game_data = gameTableGetGameData(game_table, game_id);
    if(player_id == gameDataGetPlayer(game_data, PLAYER1))
    {
        if(gameDataGetResult(game_data) == FIRST || gameDataGetResult(game_data) == GAME_DRAW)
        {
            gameTableEditGameResult(game_table, game_id, SECOND);
        }
    } else {
        if(gameDataGetResult(game_data) == SECOND || gameDataGetResult(game_data) == GAME_DRAW)
        {
            gameTableEditGameResult(game_table, game_id, FIRST);
        }
    }
    GameError error_code = gameTableDeletePlayerInGame(game_table, game_id, player_id);
    if(error_code == GAME_NULL_ARGUMENT)
    {
        return TOURNAMENT_NULL_ARGUMENT;
    }
    if(error_code == GAME_OUT_OF_MEMORY)
    {
        return TOURNAMENT_OUT_OF_MEMORY;
    }
    return TOURNAMENT_SUCCESS;
}

TournamentError tournamentTableEndTournament(TournamentTable tournament_table, TournamentId tournament_id)
{
    TournamentData tournament_data = tournamentTableGetTournamentData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    int player_table_size = gameTableGetSize(game_table) * PLAYERS_PER_GAME;
    int* player_table [STANDINGS_DATA];
    for(int i=0; i<STANDINGS_DATA; i++)
    {
        player_table[i] = malloc(player_table_size*sizeof(*player_table));
        if(player_table[i] == NULL)
        {
            return TOURNAMENT_OUT_OF_MEMORY;
        }
    }
    for(int i=0; i<player_table_size; i++)
    {
        for(int j=0; j<STANDINGS_DATA; j++)
        {
            player_table[j][i] = 0;
        }
    }
    gameTableSumUpPoints(game_table, player_table, player_table_size);
    int winner_id = tournamentTableFindWinnerInTournament(player_table, player_table_size);
    tournamentDataSetWinnerId(tournament_data, winner_id);
    //tournamentDataSetNumberOfPlayers(tournament_data, num_of_players);
    for(int i=0; i<STANDINGS_DATA; i++)
    {
        free(player_table[i]);
    }
    return TOURNAMENT_SUCCESS;
}

TournamentError tournamentTableGetStats(TournamentTable tournament_table, char* path_file)
{
    FILE* tournament_stats = fopen(path_file, "w");
    if(tournament_stats == NULL)
    {
        return TOURNAMENT_SAVE_FAILURE;
    }
    MAP_FOREACH(int *, iterator, tournament_table) {
        if(iterator == NULL)
        {
            break;
        }
        TournamentData tournament_data = tournamentTableGetTournamentData(tournament_table, *iterator);
        if(tournamentDataGetWinnerId(tournament_data) == 0)
        {
            free(iterator);
            continue;
        }
        GameTable game_table = tournamentDataGetGameTable(tournament_data);
        int tournament_num_of_games = gameTableGetSize(game_table);
        assert(tournament_num_of_games != UNDEFINED_SIZE);
        if(tournamentTablePrintStats(tournament_stats, tournament_data, tournament_num_of_games) !=
        TOURNAMENT_SUCCESS)
        {
            free(iterator);
            return TOURNAMENT_SAVE_FAILURE;
        }
        free(iterator);
    }
    fclose(tournament_stats);
    return TOURNAMENT_SUCCESS;
}

int tournamentTableGetGameTime(TournamentTable tournament_table, TournamentId tournament_id, int game_id)
{
    TournamentData tournament_data = tournamentTableGetTournamentData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(gameTableContains(game_table, game_id));
    GameData  game_data = gameTableGetGameData(game_table,game_id);
    return gameDataGetGameTime(game_data);
}

int tournamentTableGetPlayerResultInGame(TournamentTable tournament_table, TournamentId tournament_id, int game_id,
                              int player_id)
{
    TournamentData tournament_data = tournamentTableGetTournamentData(tournament_table, tournament_id);
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    assert(gameTableContains(game_table, game_id));
    GameData game_data = gameTableGetGameData(game_table, game_id);
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

static TournamentError tournamentTablePrintStats(FILE* tournament_stats, TournamentData tournament_data,
                                                 int tournament_num_of_games)
{
    int winner_id = tournamentDataGetWinnerId(tournament_data);
    int longest_game = tournamentDataGetLongestGame(tournament_data);
    double avg_time = tournamentDataGetAverageGameTime(tournament_data);
    char* location = tournamentDataGetLocation(tournament_data);
    int number_of_players = tournamentDataGetNumberOfPlayers(tournament_data);
    if (fprintf(tournament_stats, "%d\n%d\n%.2f\n%s\n%d\n%d\n", winner_id, longest_game, avg_time,
                location, tournament_num_of_games, number_of_players) == EOF) {
        fclose(tournament_stats);
        return TOURNAMENT_SAVE_FAILURE;
    }
    return TOURNAMENT_SUCCESS;
}

static int tournamentTableUpdatePlayerCount(TournamentData tournament_data, int player_id)
{
    GameTable game_table = tournamentDataGetGameTable(tournament_data);
    MAP_FOREACH(int*, iterator, game_table)
    {
        GameData game_data = gameTableGetGameData(game_table, *iterator);
        int player = gameDataGetPlayer(game_data, PLAYER1);
        if(player_id == player)
        {
            free(iterator);
            return 0;
        }
        player = gameDataGetPlayer(game_data, PLAYER2);
        if(player_id == player)
        {
            free(iterator);
            return 0;
        }
        free(iterator);
    }
    tournamentDataSetNumberOfPlayers(tournament_data,
                                     tournamentDataGetNumberOfPlayers(tournament_data)+1);
    return 1;
}

static int tournamentTableFindWinnerInTournament(int** player_table, int player_table_size)
{
    int max_points = 0;
    for(int i=0; i<player_table_size; i++)
    {
        if(player_table[POINTS_COL][i] > max_points)
        {
            max_points = player_table[POINTS_COL][i];
        }
    }
    int max_wins = 0, min_lose = MIN_LOSE_INIT, winner_id = 0;
    for(int i=0; i<player_table_size;i++)
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
static MapDataElement copyTournamentData(MapDataElement tournament_data)
{
    if(tournament_data == NULL)
    {
        return NULL;
    }

    return tournamentDataCopy(tournament_data);
}

static MapKeyElement copyTournamentId(MapKeyElement tournament_id)
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

static void freeTournamentData(MapDataElement tournament_data)
{
    if(tournament_data == NULL)
    {
        return;
    }
    tournamentDataDestroy(tournament_data);
}

static void freeTournamentId(MapKeyElement tournament_id)
{
    free(tournament_id);
}

static int compareTournamentId(MapKeyElement tournament_id1, MapKeyElement tournament_id2)
{
    assert(tournament_id1 != NULL && tournament_id2 != NULL);
    return *(int*)tournament_id1 - *(int*)tournament_id2;
}