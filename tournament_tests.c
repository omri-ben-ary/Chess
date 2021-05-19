#include "tournament_tests.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define TEST_LEN 25
void runTournamentsTest()
{
    int fake_id =0;
    int real_id =1;
    TournamentTable tournament_table = tournamentTableCreate();
    tournamentTableDestroy(tournament_table);
    tournament_table = tournamentTableCreate();
    GameTable game_table = gameTableCreate();
    TournamentData tournament_data = tournamentDataCreate("Israel", 3);
    assert(tournament_table != NULL);
    assert(tournamentTableContains(tournament_table, fake_id) == false);
    assert(tournamentTableGetTournamentData(tournament_table, fake_id) == NULL);
    //assert(tournamentTableDeleteTournament(tournament_table, fake_id) == MAP_ITEM_DOES_NOT_EXIST);
    //assert(tournamentTableAddOrEditTournament(tournament_table, fake_id, NULL ) == MAP_NULL_ARGUMENT);
    assert(tournamentTableAddOrEditTournament(tournament_table, real_id, tournament_data ) == MAP_SUCCESS);
    assert(tournamentTableContains(tournament_table, real_id) == true);
    assert(tournamentTableDeleteTournament(tournament_table, real_id) == MAP_SUCCESS);
    int ids[TEST_LEN];
    for (int i=1; i<TEST_LEN+1; i++)
    {
        ids[i-1] = i;
        assert(tournamentTableAddOrEditTournament(tournament_table, ids[i-1], tournament_data ) == MAP_SUCCESS);
    }
    assert(strcmp(tournamentDataGetLocation(tournamentTableGetTournamentData(tournament_table, 1)), "Israel") == 0);
    assert(tournamentDataGetMaxGames(tournamentTableGetTournamentData(tournament_table, 5)) == 3);
    int player_ids[100];
    for(int i=1;i<101;i++)
    {
        player_ids[i-1] = i;
    }
    double avg_check = 0;
    for(int i=0; i<TEST_LEN; i++)
    {
        avg_check += (i+1)*10;
        assert(tournamentTableAddGame(tournament_table, 7, player_ids[i], player_ids[i+1], FIRST, (i+1)*10)
        == MAP_SUCCESS);
        assert(tournamentTableAddGame(tournament_table, 8, player_ids[i], player_ids[i+1], SECOND, (i+1)*10)
        == MAP_SUCCESS);
        assert(tournamentTableAddGame(tournament_table, 9, player_ids[i], player_ids[i+1], GAME_DRAW, (i+1)*10)
        == MAP_SUCCESS);
    }
    avg_check /= TEST_LEN;
    assert(tournamentDataGetLongestGame(tournamentTableGetTournamentData(tournament_table, 7)) == 250);
    assert(tournamentDataGetAverageGameTime(tournamentTableGetTournamentData(tournament_table, 8)) == avg_check);
    assert(tournamentDataGetGameIndex(tournamentTableGetTournamentData(tournament_table, 9)) == TEST_LEN+1);
    assert(tournamentTableGetGameTime(tournament_table, 7, 8) == 80);
    assert(tournamentTableGetPlayerResultInGame(tournament_table, 7, 15, 15) == PLAYER_WIN);
    assert(tournamentTableGetPlayerResultInGame(tournament_table, 7, 15, 16) == PLAYER_LOSE);
    assert(tournamentTableGetNumberOfGames(tournament_table) == 3*TEST_LEN);

    assert(tournamentTableRemovePlayerInGame(tournament_table,9,5,5) == MAP_SUCCESS);
    assert(tournamentTableGetPlayerResultInGame(tournament_table, 9, 5, 6) == PLAYER_WIN);
    GameTable game_table_2 = tournamentDataGetGameTable(tournamentTableGetTournamentData(tournament_table,
                                                                                         9));
    GameData game_data = gameTableGetGameData(game_table_2, 5);
    assert(gameDataGetPlayer(game_data, PLAYER1) == PLAYER_NOT_FOUND);

    assert(tournamentTableRemovePlayerInGame(tournament_table,8,5,6) == MAP_SUCCESS);
    assert(tournamentTableGetPlayerResultInGame(tournament_table, 8, 5, 5) == PLAYER_WIN);
    GameTable game_table_3 = tournamentDataGetGameTable(tournamentTableGetTournamentData(tournament_table,
                                                                                         8));
    GameData game_data_2 = gameTableGetGameData(game_table_3, 5);
    assert(gameDataGetPlayer(game_data_2, PLAYER2) == PLAYER_NOT_FOUND);

    assert(tournamentTableRemovePlayerInGame(tournament_table,7,1,1) == MAP_SUCCESS);
    assert(tournamentTableGetPlayerResultInGame(tournament_table, 8, 1, 2) == PLAYER_WIN);
    GameTable game_table_4 = tournamentDataGetGameTable(tournamentTableGetTournamentData(tournament_table,
                                                                                         7));
    GameData game_data_3 = gameTableGetGameData(game_table_4, 1);
    assert(gameDataGetPlayer(game_data_3, PLAYER1) == PLAYER_NOT_FOUND);

    assert(tournamentTableAddGame(tournament_table, 1, player_ids[0], player_ids[1], GAME_DRAW, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[0], player_ids[2], FIRST, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[1], player_ids[2], FIRST, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[0], player_ids[3], SECOND, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[1], player_ids[3], SECOND, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[0], player_ids[4], FIRST, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[1], player_ids[4], FIRST, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[1], player_ids[5], FIRST, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[0], player_ids[5], GAME_DRAW, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[0], player_ids[6], GAME_DRAW, 11) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[3], player_ids[4], FIRST, 10) == MAP_SUCCESS);
    assert(tournamentTableAddGame(tournament_table, 1, player_ids[3], player_ids[5], GAME_DRAW, 10) == MAP_SUCCESS);
    assert(tournamentTableEndTournament(tournament_table, 1) == MAP_SUCCESS);
    assert(tournamentTableEndTournament(tournament_table, 7) == MAP_SUCCESS);
    assert(tournamentTableEndTournament(tournament_table, 8) == MAP_SUCCESS);
    TournamentData tournament_data_1 = tournamentTableGetTournamentData(tournament_table, 1);
    //assert(tournamentDataGetWinnerId(tournament_data_1) == player_ids[3]);
    printf("%d\n", tournamentDataGetWinnerId(tournament_data_1));

    assert(tournamentTableGetStatsOfTournament(tournament_table, "C:\\Users\\User\\stats.txt") == MAP_SUCCESS);
    tournamentTableDestroy(tournament_table);
    gameTableDestroy(game_table);
    tournamentDataDestroy(tournament_data);
}