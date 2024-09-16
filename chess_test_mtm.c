#include <stdlib.h>
#include "chessSystem.h"
#include "test_utilities.h"
#include <math.h>

/*The number of tests*/
#define NUMBER_TESTS 18
#define PRECISION 0.00001
#define OUR_PATH_LEVEL "../tests/player_levels_your_output.txt"
#define OUR_PATH_STATS "../tests/tournament_statistics_your_output.txt"
bool testChessAddTournament() {
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 5, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 1, 10, "Paris") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    // location
    ASSERT_TEST(chessAddTournament(chess, 4, 5, "paris") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 6, 5, "Paris!") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(chess, 7, 5, "Par is") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 8, 5, "Par is!") == CHESS_INVALID_LOCATION);
    // max games
    ASSERT_TEST(chessAddTournament(chess, 4, -2, "Tokyo") == CHESS_INVALID_MAX_GAMES);
    // null
    ASSERT_TEST(chessAddTournament(chess, 4, -2, NULL) == CHESS_NULL_ARGUMENT);
    // invalid id
    ASSERT_TEST(chessAddTournament(chess, -1, 5, "Par is") == CHESS_INVALID_ID);
    // check order of errors
    // id + location + games
    ASSERT_TEST(chessAddTournament(chess, -1, -1, "!ar is") == CHESS_INVALID_ID);
    // location + games + already
    ASSERT_TEST(chessAddTournament(chess, 1, -1, "!ar is") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    // location + max games
    ASSERT_TEST(chessAddTournament(chess, 10, -1, "!ar is") == CHESS_INVALID_LOCATION);
    chessDestroy(chess);
    return true;
}

bool testChessRemoveTournament() {
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Paris") == CHESS_SUCCESS);

    chessDestroy(chess);
    return true;
}

bool testChessAddGame(){
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "London") == CHESS_SUCCESS);

    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    // error order
    ASSERT_TEST(chessAddGame(NULL, -1, -1, -2, FIRST_PLAYER, -2000) == CHESS_NULL_ARGUMENT);
    // invalid tournament id
    ASSERT_TEST(chessAddGame(chess, -1, -1, -2, FIRST_PLAYER, -2000) == CHESS_INVALID_ID);
    // two players
    ASSERT_TEST(chessAddGame(chess, 1, -1, -2, FIRST_PLAYER, -2000) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, 1, 1, -2, FIRST_PLAYER, -2000) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(chess, 1, -1, 2, FIRST_PLAYER, -2000) == CHESS_INVALID_ID);
    // not exists
    ASSERT_TEST(chessAddGame(chess, 4, 1, 2, FIRST_PLAYER, -2000) == CHESS_TOURNAMENT_NOT_EXIST);
    // ended
    ASSERT_TEST(chessEndTournament(chess, 2) == CHESS_NO_GAMES);
    ASSERT_TEST(chessAddGame(chess, 2, 1, 2, FIRST_PLAYER, 3) == CHESS_SUCCESS);
    // already exists
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, -2000) == CHESS_GAME_ALREADY_EXISTS);
    // invalid play time
    ASSERT_TEST(chessAddGame(chess, 1, 5, 2, FIRST_PLAYER, -1) == CHESS_INVALID_PLAY_TIME);
    for(int i = 1; i < 10; i++){
        if(i < 5){
            ASSERT_TEST(chessAddGame(chess, 1, 7900, i, FIRST_PLAYER, 19) == CHESS_SUCCESS);
        }else{
            ASSERT_TEST(chessAddGame(chess, 1, 7900, i, FIRST_PLAYER, 19) == CHESS_EXCEEDED_GAMES);
        }
    }
    // play against yourself
    ASSERT_TEST(chessAddGame(chess, 1, 2, 2, FIRST_PLAYER, 1) == CHESS_INVALID_ID);
    // switch player order
    ASSERT_TEST(chessAddGame(chess, 1, 2, 1, FIRST_PLAYER, 1) == CHESS_GAME_ALREADY_EXISTS);

    chessDestroy(chess);
    return true;
}

bool testAvgPlayTime()
{
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 3, FIRST_PLAYER, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 3, 2, SECOND_PLAYER, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 4, 1, SECOND_PLAYER, 4) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 2, 4, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 3, 4, DRAW, 6) == CHESS_SUCCESS);
    // test avg times
    ChessResult result;
    ASSERT_TEST((chessCalculateAveragePlayTime(chess, 1, &result) - (double)7/3) < PRECISION);
    ASSERT_TEST(result == CHESS_SUCCESS);
    ASSERT_TEST(chessCalculateAveragePlayTime(chess, 2, &result) ==(double)3);
    ASSERT_TEST(result == CHESS_SUCCESS);
    ASSERT_TEST(fabs(chessCalculateAveragePlayTime(chess, 3, &result) - (double)11/3) < PRECISION);
    ASSERT_TEST(result == CHESS_SUCCESS);
    // removing players and recalculating
    ASSERT_TEST(chessRemovePlayer(chess, 1)==CHESS_SUCCESS);
    ASSERT_TEST(chessCalculateAveragePlayTime(chess, 1, &result) == 0);
    ASSERT_TEST(result == CHESS_PLAYER_NOT_EXIST);
    // check remaining players stayed the same
    ASSERT_TEST(chessCalculateAveragePlayTime(chess, 2, &result) ==(double)3);
    ASSERT_TEST(result == CHESS_SUCCESS);
    ASSERT_TEST(fabs(chessCalculateAveragePlayTime(chess, 3, &result) - (double)11/3) < PRECISION);
    ASSERT_TEST(result == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessCalculateAveragePlayTime(chess, 1, &result) == 1);
    ASSERT_TEST(result == CHESS_SUCCESS);
    ASSERT_TEST(chessCalculateAveragePlayTime(chess, 2, &result) ==(double)10/4);
    ASSERT_TEST(result == CHESS_SUCCESS);
    chessDestroy(chess);
    return true;
}

bool testChessPrintLevelsAndTournamentStatistics(){

    char* our_path_level = OUR_PATH_LEVEL;
    //char* our_path_stats = OUR_PATH_STATS;

    FILE* file_levels = fopen(our_path_level, "w");
    /*if(!file_levels){
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /tests/player_levels_your_output.txt");
        return false;
    }*/
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    //ASSERT_TEST(chessAddGame(chess, 1, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    //ASSERT_TEST(chessAddGame(chess, 1, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    //ASSERT_TEST(chessAddGame(chess, 1, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    //ASSERT_TEST(chessAddGame(chess, 1, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    //ASSERT_TEST(chessAddGame(chess, 1, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    //ASSERT_TEST(chessEndTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
//    ASSERT_TEST(chessSaveTournamentStatistics(chess, our_path_stats) == CHESS_SUCCESS);
    chessDestroy(chess);
    fclose(file_levels);

    // 2

   // file_levels = fopen(our_path_level, "w");
    // tournament not ended
    //ChessSystem chess2 = chessCreate();
    /**
     * p4 w: 3 l:0 t:0 -> 6.00
     * p2 w: 2 l: 1 t:0 -> 0.67
     * p3 w:0 l:2 t:1 -> -6.00
     * p1 w: l:2 t:1 -> -6.00
     * */
   /* ASSERT_TEST(chessAddTournament(chess2, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess2, 1, 4, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess2, 1, 4, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess2, 1, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess2, 1, 1, 4, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess2, 1, 2, 1, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess2, 1, 3, 1, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess2, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess2, our_path_stats) == CHESS_NO_TOURNAMENTS_ENDED);
    ASSERT_TEST(compareFiles(our_path_stats, "../expected_files/stats/tournament_not_ended.txt") == 1);
    fclose(file_levels);
//    ASSERT_TEST(compareFiles(our_path_level, "../expected_files/level/tournament_not_ended.txt") == 1);
    file_levels = fopen(our_path_level, "w");

    // 3

    ASSERT_TEST(chessEndTournament(chess2, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess2, 4) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess2, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess2, our_path_stats) == CHESS_SUCCESS);
    // the number of players? we remove from tournament that ended.

//    ASSERT_TEST(compareFiles(our_path_stats, "../expected_files/stats/remove_from_ended") == 1);

    fclose(file_levels);
    // remove player
//    ASSERT_TEST(compareFiles(our_path_level, "../expected_files/level/remove_from_ended") == 1);
    chessDestroy(chess2);

    // 4
    /**
     * p4 w:1 l:1 t:1 -> -0.67
     * p2 w: 3 l: 0 t:0 -> 6.00
     * p3 w:1 l:1 t:1 -> -0.67
     * */
    /*file_levels = fopen(our_path_level, "w");
    ChessSystem chess3 = chessCreate();
    ASSERT_TEST(chessAddTournament(chess3, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess3, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess3, 1, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess3, 1, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess3, 1, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess3, 1, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess3, 1, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess3, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess3, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess3, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
    ASSERT_TEST(chessSaveTournamentStatistics(chess3, our_path_stats) == CHESS_SUCCESS);
//    ASSERT_TEST(compareFiles(our_path_stats, "../expected_files/stats/removed_player") == 1);
 //   ASSERT_TEST(compareFiles(our_path_level, "../expected_files/level/removed_player") == 1);
    chessDestroy(chess3);

    // 5
    /**
     * p4 w:2 l:0 t:1 -> 4.67
     * p3 w:2 l:0 t:1 -> 4.67
     * */
    /*file_levels = fopen(our_path_level, "w");
    ChessSystem chess4 = chessCreate();
    ASSERT_TEST(chessAddTournament(chess4, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess4, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess4, 1, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess4, 1, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess4, 1, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess4, 1, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess4, 1, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess4, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess4, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess4, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess4, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess4, our_path_stats) == CHESS_SUCCESS);
//    ASSERT_TEST(compareFiles(our_path_stats, "../expected_files/stats/two_players_removed") == 1);
    fclose(file_levels);
//    ASSERT_TEST(compareFiles(our_path_level, "../expected_files/level/two_players_removed") == 1);
    chessDestroy(chess4);
    // 6

    /**
     * p1 w: 3 l:0 t:0 -> 6.00
     * p4 w:1 l:3 t:2 -> -3.32
     * p2 w: 5 l: 1 t:0 -> 3.32
     * p3 w:1 l:3 t:2 -> -3.32
     * */

    /*file_levels = fopen(our_path_level, "w");
    ChessSystem chess5 = chessCreate();
    ASSERT_TEST(chessAddTournament(chess5, 3, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 3, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 3, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 3, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 3, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 3, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 3, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(chess5, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess5, 3) == CHESS_SUCCESS);

    // tournament 2
    ASSERT_TEST(chessAddTournament(chess5, 2, 4, "Tokyo") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 2, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 2, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 2, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 2, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 2, 2, 4, FIRST_PLAYER, 4000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess5, 2, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess5, 2) == CHESS_SUCCESS);


    ASSERT_TEST(chessSavePlayersLevels(chess5, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
    ASSERT_TEST(chessSaveTournamentStatistics(chess5, our_path_stats) == CHESS_SUCCESS);
//    ASSERT_TEST(compareFiles(our_path_stats, "../expected_files/stats/two_tournaments") == 1);
 //   ASSERT_TEST(compareFiles(our_path_level, "../expected_files/level/two_tournaments") == 1);
    chessDestroy(chess5);*/
    return true;
}

bool insaneChallengeTest(){
    ChessSystem chess = chessCreate();
    for(int i = 1; i < 1001; i ++){
        ASSERT_TEST(chessAddTournament(chess, i, 2000, "London") == CHESS_SUCCESS);
    }
    for(int i = 1; i < 1001; i ++){
        for(int j = 1; j < 11; j ++) {
            ASSERT_TEST(chessAddGame(chess, i, 12111, j, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
    }
    chessDestroy(chess);
    ChessSystem chess2 = chessCreate();
    ASSERT_TEST(chessAddTournament(chess2, 1, 2000, "London") == CHESS_SUCCESS);
    for(int i = 1; i < 1001; i ++){
        ASSERT_TEST(chessAddGame(chess2, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        ASSERT_TEST(chessRemovePlayer(chess2, 1)==CHESS_SUCCESS);
    }
    ASSERT_TEST(chessEndTournament(chess2, 1) == CHESS_SUCCESS);
    char* our_path_level = "../tests/player_levels_your_output.txt";
    char* our_path_stats = "../tests/tournament_statistics_your_output.txt";
    FILE* file_levels = fopen("../tests/player_levels_your_output.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(chess2, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess2, "../tests/tournament_statistics_your_output.txt") == CHESS_SUCCESS);
 //   ASSERT_TEST(compareFiles(our_path_stats, "../expected_files/stats/insane") == 1);
    fclose(file_levels);
 //   ASSERT_TEST(compareFiles(our_path_level, "../expected_files/level/insane") == 1);
    chessDestroy(chess2);
    // sort ranks test
    ChessSystem chess3 = chessCreate();
    ASSERT_TEST(chessAddTournament(chess3, 1, 2000, "London") == CHESS_SUCCESS);
    for(int i = 1; i < 1001; i++)
    {
        if (i < 100)
        {
            ASSERT_TEST(chessAddGame(chess3,1, 12111, i, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
        if (i > 200 && i < 900)
        {
            ASSERT_TEST(chessAddGame(chess3,1, i, i+1, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
        if (i > 900 && i < 950)
        {
            ASSERT_TEST(chessAddGame(chess3,1, i+3, i+1, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
    }
    for (int j = 1; j < 150; j++)
    {
        ASSERT_TEST(chessAddGame(chess3,1, 1000, j, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    }
    file_levels = fopen("../tests/player_levels_your_output.txt", "w");
    ASSERT_TEST(chessSavePlayersLevels(chess3, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
    chessDestroy(chess3);
    return true;
}

//segel tests
bool testChessAddTournament_segel() {
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 5, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 1, 10, "Paris") == CHESS_TOURNAMENT_ALREADY_EXISTS);

    chessDestroy(chess);
    return true;
}

bool testChessRemoveTournament_segel() {
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(chess, 2, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(chess, 1) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "Paris") == CHESS_SUCCESS);

    chessDestroy(chess);
    return true;
}

bool testChessAddGame_segel(){
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);

    chessDestroy(chess);
    return true;
}

bool testChessPrintLevelsAndTournamentStatistics_segel(){
    char* our_path_level = OUR_PATH_LEVEL;
    char* our_path_stats = OUR_PATH_STATS;
    FILE* file_levels = fopen(our_path_level, "w");
    if(!file_levels){
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /tests/player_levels_your_output.txt");
        return false;
    }
    ChessSystem chess = chessCreate();
    ASSERT_TEST(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 1, 3, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 3, 2, SECOND_PLAYER, 3000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 4, 1, SECOND_PLAYER, 1000) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 2, 4, FIRST_PLAYER, 3500) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(chess, 1, 3, 4, DRAW, 400) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(chess, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSavePlayersLevels(chess, file_levels) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(chess, our_path_stats) == CHESS_SUCCESS);
    fclose(file_levels);
//    ASSERT_TEST(compareFiles(our_path_level, "../expected_output/player_levels_expected_output.txt") == 1);

    chessDestroy(chess);
    //fclose(file_levels);
    return true;
}

//maaroof the ashkiller tests:
bool testChessDestroy_maaroof() {
    chessDestroy(NULL);

    ChessSystem sys1 = chessCreate();
    chessDestroy(sys1);

    ChessSystem sys2 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys2, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys2, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys2, 3, 1, "Location three") == CHESS_SUCCESS);
    chessDestroy(sys2);

    ChessSystem sys3 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys3, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys3, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys3, 3, 1, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys3, 1, 01, 02, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys3, 2, 01, 02, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys3, 3, 01, 02, FIRST_PLAYER, 5) == CHESS_SUCCESS);
    chessDestroy(sys3);

    return true;
}

bool testChessAddTournamentAndEndTournament_maaroof() {
    ChessSystem sys1 = chessCreate();

    ASSERT_TEST(chessAddTournament(sys1, 1, 1, NULL) == CHESS_NULL_ARGUMENT);
    ASSERT_TEST(chessAddTournament(NULL, 1, 1, "Location one") == CHESS_NULL_ARGUMENT);

    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 1, "Location three") == CHESS_SUCCESS);

    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "Location one") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "invalid location") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(sys1, 4, -1, "invalid location") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(sys1, 4, -1, "London") == CHESS_INVALID_MAX_GAMES);

    ASSERT_TEST(chessAddTournament(sys1, -2, -1, "invalid location") == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddTournament(sys1, 2, -1, "invalid location") == CHESS_TOURNAMENT_ALREADY_EXISTS);
    ASSERT_TEST(chessAddTournament(sys1, 5, 1, "invalid location") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(sys1, 5, 1, " Invalid location") == CHESS_INVALID_LOCATION);
    ASSERT_TEST(chessAddTournament(sys1, 10, 1, "L") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, SECOND_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, SECOND_PLAYER, 10) == CHESS_SUCCESS);

    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_TOURNAMENT_ENDED);
    ASSERT_TEST(chessEndTournament(sys1, 4) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessEndTournament(sys1, -1) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, 1, 4, 5, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_ENDED);

    char* our_path_level = OUR_PATH_LEVEL;
    char* our_path_stats = OUR_PATH_STATS;
    FILE* file_levels = fopen(our_path_level, "w");
    if(!file_levels){
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /tests/player_levels_your_output.txt");
        return false;
    }
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, our_path_stats) == CHESS_SUCCESS);
 //   ASSERT_TEST(compareFiles(our_path_stats, "../expected_output/test_add_tournament_end_tournament_expected_output.txt") == 1);

    ChessSystem sys2 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys2, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys2, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys2, our_path_stats) == CHESS_NO_TOURNAMENTS_ENDED);
    fclose(file_levels);
    chessDestroy(sys2);
    chessDestroy(sys1);
    return true;
}

bool testChessAddGame_maaroof()
{
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 1, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 1, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 1, "Location three") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    int player_4 = 4;

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_2, player_1, FIRST_PLAYER, 10) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);

    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_3, FIRST_PLAYER, 10) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_4, FIRST_PLAYER, -1) == CHESS_INVALID_PLAY_TIME);
    // ZERO play time
    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_4, FIRST_PLAYER, 0) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, -1, player_1, player_2, FIRST_PLAYER, -1) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, 1, -8, player_2, FIRST_PLAYER, -1) == CHESS_INVALID_ID);

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_3, SECOND_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_1, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_4, SECOND_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);
    ASSERT_TEST(chessAddGame(sys1, 4, player_1, player_2, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_NOT_EXIST);

    ASSERT_TEST(chessAddTournament(sys1, 4, 2, "Location four") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_2, SECOND_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_2, FIRST_PLAYER, 10) == CHESS_GAME_ALREADY_EXISTS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_4, player_2, FIRST_PLAYER, 10) == CHESS_EXCEEDED_GAMES);

    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_4, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(sys1,player_3) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 4, player_3, player_4, FIRST_PLAYER, 10) == CHESS_SUCCESS);

    chessDestroy(sys1);
    return true;
}

bool testRemoveTournament_maaroof() {
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 3, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(sys1, 3) == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    //int player_4 = 4;

    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_3, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemoveTournament(sys1, 2) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_TOURNAMENT_NOT_EXIST);
    ASSERT_TEST(chessAddGame(sys1, 2, -1, player_2, FIRST_PLAYER, 10) == CHESS_INVALID_ID);
    ASSERT_TEST(chessAddGame(sys1, -1, player_1, player_2, FIRST_PLAYER, -10) == CHESS_INVALID_ID);

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);
    char *our_path_level = OUR_PATH_LEVEL;
    char *our_path_stats = OUR_PATH_STATS;
    FILE *file_levels = fopen(our_path_level, "w");
    if (!file_levels) {
        printf("test failed to open file, make sure you have the folder tests in the same folder with chessSystem"
               "excutable file and you have write permissions for the file /tests/player_levels_your_output.txt");
        return false;}
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, our_path_stats) ==
                CHESS_NO_TOURNAMENTS_ENDED);

    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, our_path_stats) == CHESS_SUCCESS);
//    ASSERT_TEST(compareFiles("../expected_output/test_tournament_remove_expected_output.txt", our_path_stats) == 1);
    fclose(file_levels);
    chessDestroy(sys1);
    return true;
    }

bool testChessRemovePlayer_maaroof() {


    char *our_path_level = OUR_PATH_LEVEL;
//    char *our_path_stats = OUR_PATH_STATS;
    FILE *file_levels = fopen(our_path_level, "w");
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    //int player_4 = 4;

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2
    ASSERT_TEST(chessAddGame(sys1, 1, player_3, player_2, FIRST_PLAYER, 4) == CHESS_SUCCESS); //tour 1: add 3,2
    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 10) == CHESS_SUCCESS);//tour 2: add 1,2

    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
 //   ASSERT_TEST(compareFiles("../expected_output/player_levels_all.txt", our_path_level) == 1);


    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);//remove 1
    ASSERT_TEST(chessEndTournament(sys1, 1) == CHESS_SUCCESS);//end 1
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);//end 2

    file_levels = fopen(our_path_level, "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels) == CHESS_SUCCESS);//print
    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_PLAYER_NOT_EXIST);
    fclose(file_levels);

 //   ASSERT_TEST(compareFiles("../expected_output/remove_player_1.txt", our_path_level) == 1);

    chessDestroy(sys1);
    return true;
}

bool testChessRemovePlayer_2_maaroof() {


    char* our_path_level = OUR_PATH_LEVEL;
//    char* our_path_stats = OUR_PATH_STATS;
    FILE* file_levels = fopen(our_path_level, "w");
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2

    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
    chessDestroy(sys1);
 //   ASSERT_TEST(compareFiles(our_path_level, "../expected_output/before_remove.txt") == 1);

    /*ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);//remove 1

    file_levels = fopen(our_path_level, "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);

//    ASSERT_TEST(compareFiles(our_path_level, "../expected_output/after_remove.txt") == 1);


    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2

    file_levels = fopen(our_path_level, "w");
    ASSERT_TEST(chessSavePlayersLevels(sys1, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);

//    ASSERT_TEST(compareFiles(our_path_level, "../expected_output/add_same_game_after_remove.txt") == 1);


    chessDestroy(sys1);*/
    return true;
}

bool testAvgGameTime_maaroof()
{
    ChessSystem sys1 = chessCreate();
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    int player_3 = 3;
    int player_4 = 4;

    ChessResult* chess_result = malloc(sizeof(*chess_result));
    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS); //tour 1: add 1,2
    double avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    double avg2 = chessCalculateAveragePlayTime(sys1, player_2, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == avg2);
    ASSERT_TEST(avg1 == 6);

    ASSERT_TEST(chessAddGame(sys1, 1, player_1, player_3, FIRST_PLAYER, 14) == CHESS_SUCCESS);
    avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 10);

    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 14);

    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_3, FIRST_PLAYER, 20) == CHESS_SUCCESS);
    avg1 = chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 40.0/3.0);

    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 17);

    chessCalculateAveragePlayTime(sys1, player_4, chess_result);
    ASSERT_TEST(*chess_result == CHESS_PLAYER_NOT_EXIST);

    chessCalculateAveragePlayTime(sys1, -1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_INVALID_ID);

    chessCalculateAveragePlayTime(NULL, player_4, chess_result);
    ASSERT_TEST(*chess_result == CHESS_NULL_ARGUMENT);

    chessCalculateAveragePlayTime(NULL, -1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_NULL_ARGUMENT);

    ASSERT_TEST(chessRemovePlayer(sys1, player_1) == CHESS_SUCCESS);
    chessCalculateAveragePlayTime(sys1, player_1, chess_result);
    ASSERT_TEST(*chess_result == CHESS_PLAYER_NOT_EXIST);

    avg1 = chessCalculateAveragePlayTime(sys1, player_3, chess_result);
    ASSERT_TEST(*chess_result == CHESS_SUCCESS);
    ASSERT_TEST(avg1 == 17);

    free(chess_result);
    chessDestroy(sys1);
    return true;
}

bool testSavePlayerLevelsAndTournamentStatistics_maaroof()
{
    ChessSystem sys1 = chessCreate();
//    char* our_path_level = OUR_PATH_LEVEL;
    char* our_path_stats = OUR_PATH_STATS;
//    FILE* file_levels = fopen(our_path_level, "w");
    ASSERT_TEST(chessAddTournament(sys1, 1, 3, "Location one") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 2, 3, "Location two") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 3, 3, "Location three") == CHESS_SUCCESS);
    ASSERT_TEST(chessAddTournament(sys1, 4, 3, "Location four") == CHESS_SUCCESS);

    int player_1 = 1;
    int player_2 = 2;
    //int player_3 = 3;
    //int player_4 = 4;
    //int player_5 = 5;

    ASSERT_TEST(chessAddGame(sys1, 4, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 4) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, our_path_stats) == CHESS_SUCCESS);


//    ASSERT_TEST(compareFiles(our_path_stats, "../expected_output/tournament_statistics_1.txt") == 1);


    ASSERT_TEST(chessAddGame(sys1, 3, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessRemovePlayer(sys1, 1));
    ASSERT_TEST(chessEndTournament(sys1, 3) == CHESS_SUCCESS);
    ASSERT_TEST(chessSaveTournamentStatistics(sys1, our_path_stats) == CHESS_SUCCESS);

 //   ASSERT_TEST(compareFiles("../expected_output/tournament_statistics_2.txt", our_path_stats) == 1);

    ASSERT_TEST(chessAddGame(sys1, 2, player_1, player_2, FIRST_PLAYER, 6) == CHESS_SUCCESS);
    ASSERT_TEST(chessEndTournament(sys1, 2) == CHESS_SUCCESS);

    ASSERT_TEST(chessSaveTournamentStatistics(sys1, our_path_stats) == CHESS_SUCCESS);


//    ASSERT_TEST(compareFiles(our_path_stats,"../expected_output/tournament_statistics_3.txt") == 1);

    chessDestroy(sys1);
    return true;
}


/*The names of the test functions should be added here*/
const char* testNames[] = {
        "testChessAddTournament",
        "testChessRemoveTournament",
        "testChessAddGame",
        "testChessPrintLevelsAndTournamentStatistics",
        "testAvgPlayTime",
        "insaneChallengeTest",
        "testChessAddTournament_segel",
        "testChessRemoveTournament_segel",
        "testChessAddGame_segel",
        "testChessPrintLevelsAndTournamentStatistics_segel",
        "testChessDestroy_maaroof",
        "testChessAddTournamentAndEndTournament_maaroof",
        "testChessAddGame_maaroof",
        "testRemoveTournament_maaroof",
        "testChessRemovePlayer_maaroof",
        "testChessRemovePlayer_2_maaroof",
        "testAvgGameTime_maaroof",
        "testSavePlayerLevelsAndTournamentStatistics_maaroof"
};


/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
        testChessAddTournament,
        testChessRemoveTournament,
        testChessAddGame,
        testChessPrintLevelsAndTournamentStatistics,
        testAvgPlayTime,
        insaneChallengeTest,
        testChessAddTournament_segel,
        testChessRemoveTournament_segel,
        testChessAddGame_segel,
        testChessPrintLevelsAndTournamentStatistics_segel,
        testChessDestroy_maaroof,
        testChessAddTournamentAndEndTournament_maaroof,
        testChessAddGame_maaroof,
        testRemoveTournament_maaroof,
        testChessRemovePlayer_maaroof,
        testChessRemovePlayer_2_maaroof,
        testAvgGameTime_maaroof,
        testSavePlayerLevelsAndTournamentStatistics_maaroof
};

int main(int argc, char *argv[]) {
    if (argc == 1) {
        for (int test_idx = 3; test_idx < 4; test_idx++) {
            RUN_TEST(tests[test_idx], testNames[test_idx]);
        }
        return 0;
    }
    if (argc != 2) {
        fprintf(stdout, "Usage: chessSystem <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS) {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
    return 0;
}