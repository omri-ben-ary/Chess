//
// Created by DELL on 15/05/2021.
//

//TODO: 1. understand what is going on with the null pointer
//      2. put only gives me the copy and i should free it?
//      3. player 1 stats

#include "players_map_tests.h"
#include "players_map.h"
#include "stdio.h"
#include "assert.h"
#include "stdlib.h"
void test_of_players_map()
{
    // NULL POINTERS CHECK!
    assert(playersMapContain(NULL,12345) == false);
    playersMapDestroy(NULL); // NO MEMORY LEAKS
    assert(playersMapGetStats(NULL, 1234) == NULL);
    assert(playersMapAddGameStats(NULL, 1234, 1234, 1234, 12) == TOURNAMENT_STATS_NULL_POINTER);
    int my_id = 12345;
    assert(playersMapRemove(NULL,my_id) == MAP_NULL_ARGUMENT);
    assert(playersMapPut(NULL,my_id,NULL) == MAP_NULL_ARGUMENT);
    assert(playersMapGetTournaments(NULL,my_id) == NULL);
    assert(playersMapGetGamesInTournament(NULL,my_id, 1234) == NULL);
    playersMapRemoveTournament(NULL, my_id, 12345); // NO MEMORY LEAKS

    // CHECK PLAYER MAP NORMAL BEHAVIOR

    Players players_map_1 = playersMapCreate();
    playersMapDestroy(players_map_1);
    players_map_1 = playersMapCreate();
    int player1_id = 123;
    PlayerStats player1_stats = playerStatsCreate();
    assert(playersMapPut(players_map_1,player1_id, player1_stats) == MAP_SUCCESS);
    playerStatsDestroy(player1_stats);

    int player2_id = 1234;
    PlayerStats player2_stats = NULL;
    assert(playersMapPut(players_map_1,player2_id, player2_stats) == MAP_NULL_ARGUMENT);
    assert(playersMapAddGameStats(players_map_1, player2_id , 11111, 11111, 2) == TOURNAMENT_STATS_NULL_POINTER);
    player2_stats = playerStatsCreate();
    assert(playersMapPut(players_map_1,player2_id, player2_stats) == MAP_SUCCESS);
    playerStatsDestroy(player2_stats);

    int tournament1_id = 111111;
    int game1_id = 12345;
    int max_games_per_tournament_1 = 2;
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament1_id, game1_id, max_games_per_tournament_1) == GAME_STATS_ADD_SUCCESS);
    player1_stats = playersMapGetStats(players_map_1,player1_id);
    assert(playerStatsSearchForTournament(player1_stats,tournament1_id) == true);
    int game2_id = 12345;
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament1_id, game2_id, max_games_per_tournament_1) == GAME_ID_IS_ALREADY_TAKEN);
    assert(playerStatsSearchForTournament(player1_stats,tournament1_id) == true);
    int game3_id = 1111111;
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament1_id, game3_id, max_games_per_tournament_1) == GAME_STATS_ADD_SUCCESS);
    int game4_id = 20825;
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament1_id, game4_id, max_games_per_tournament_1) == TOURNAMENT_STATS_FULL_OF_GAMES);

    int player3_id = 11111;
    PlayerStats player3_stats = playerStatsCreate();
    assert(playersMapPut(players_map_1,player3_id, player3_stats) == MAP_SUCCESS);
    assert(playersMapRemove(players_map_1, player3_id) == MAP_SUCCESS);
    playerStatsDestroy(player3_stats);

    int tournament2_id = 22222222;
    int max_games_per_tournament_2 = 1;
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament2_id, game1_id, max_games_per_tournament_2) == GAME_STATS_ADD_SUCCESS);
    assert(playerStatsSearchForTournament(player1_stats,tournament1_id) == true);
    int tournament3_id = 33333333;
    int max_games_per_tournament_3 = 3;
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament3_id, game4_id, max_games_per_tournament_3) == GAME_STATS_ADD_SUCCESS);
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament3_id, game1_id, max_games_per_tournament_3) == GAME_STATS_ADD_SUCCESS);
    assert (playersMapAddGameStats(players_map_1, player1_id , tournament3_id, game3_id, max_games_per_tournament_3) == GAME_STATS_ADD_SUCCESS);
    assert(playerStatsSearchForTournament(player1_stats,tournament1_id) == true);
    assert(playerStatsSearchForTournament(player1_stats,tournament2_id) == true);
    assert(playerStatsSearchForTournament(player1_stats,tournament3_id) == true);

    //CHECK FOREACH BEHAVIOR
    int* player1_tournaments = NULL;
    player1_tournaments = playersMapGetTournaments(players_map_1, player1_id);
    if (!(player1_tournaments == NULL))
    {
        int num_of_tournaments_player1 = 0;
        int i = 0;
        while (player1_tournaments[i++])
        {
            num_of_tournaments_player1++;
        }
        //printf("Num of tournaments of player 1: %d\n", num_of_tournaments_player1);
        for (i = 0; i < num_of_tournaments_player1; i++)
        {
            int num_of_games_per_tournament = playersMapGetMaxGamesForTournament(players_map_1,player1_id, player1_tournaments[i]);
            int *player1_games = playersMapGetGamesInTournament(players_map_1, player1_id, player1_tournaments[i]);
            if (!(player1_games == NULL))
            {
                for (int j = 0; j < num_of_games_per_tournament; j++)
                {
                    //printf("tournament_id: %d, game_id: %d\n", player1_tournaments[i], player1_games[j]);
                }
            }
            free(player1_games);
        }
        free(player1_tournaments);
    }
    //printf("\n\n now we remove one:\n");
    playersMapRemoveTournament(players_map_1, player1_id, tournament2_id);

    player1_tournaments = playersMapGetTournaments(players_map_1, player1_id);
    if (!(player1_tournaments == NULL))
    {
        int num_of_tournaments_player1 = 0;
        int i = 0;
        while (player1_tournaments[i++])
        {
            num_of_tournaments_player1++;
        }
        //printf("Num of tournaments of player 1: %d\n", num_of_tournaments_player1);
        for (i = 0; i < num_of_tournaments_player1; i++)
        {
            int num_of_games_per_tournament = playersMapGetMaxGamesForTournament(players_map_1,player1_id, player1_tournaments[i]);
            int *player1_games = playersMapGetGamesInTournament(players_map_1, player1_id, player1_tournaments[i]);
            if (!(player1_games == NULL))
            {
                for (int j = 0; j < num_of_games_per_tournament; j++)
                {
                    //printf("tournament_id: %d, game_id: %d\n", player1_tournaments[i], player1_games[j]);
                }
            }
            free(player1_games);
        }
        free(player1_tournaments);
    }

    // CHECK THE PLAYER STATS BEHAVIOR
    for (int  i = 0 ; i < 20 ; i++)
    {
        int divider = i%3;
        switch (divider)
        {
            case 0:
                playersMapAddWin(players_map_1, player1_id);
                break;
            case 1:
                playersMapAddTie(players_map_1, player1_id);
                break;
            case 2:
                playersMapAddLose(players_map_1, player1_id);
                break;
            default:
                break;
        }
    }
    printf("player 1 wins amount: %d\n", playersMapGetWins(players_map_1, player1_id));
    printf("player 1 ties amount: %d\n", playersMapGetTies(players_map_1, player1_id));
    printf("player 1 loses amount: %d\n", playersMapGetLoses(players_map_1, player1_id));

    PlayersMapNullifyAllPlayerStats(players_map_1);

    printf("player 1 wins amount: %d\n", playersMapGetWins(players_map_1, player1_id));
    printf("player 1 ties amount: %d\n", playersMapGetTies(players_map_1, player1_id));
    printf("player 1 loses amount: %d\n", playersMapGetLoses(players_map_1, player1_id));

    assert(playersMapContain(players_map_1, player1_id) == true);
    playersMapDestroy(players_map_1);




    /*
    tournamentStatsDestroy(tournament1_stats);
    tournamentStatsDestroy(tournament2_stats);
    tournamentStatsDestroy(tournament3_stats);
    tournamentStatsDestroy(tournament4_stats);
    tournamentsHistoryTableDestroy(my_tournaments_history_table);
    */
}