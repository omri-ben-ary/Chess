#include "game_tests.h"
#include "tournament_tests.h"
#include "chessSystem.h"
#include <assert.h>
#include "chessSystemTests.h"
#include <stdbool.h>
bool testChessRemovePlayer();
bool testSaveTournamentStatistics();
bool testJunkValues();
bool insaneChallengeTest();
int main()
{
    //runGameTests();
    //runTournamentsTest();
    //assert(testChessRemovePlayer() == true);
    //assert(testSaveTournamentStatistics() == true);
    //assert(testJunkValues() == true);
    //tests_of_chess();
    insaneChallengeTest();
    return 0;
}

bool insaneChallengeTest(){
     ChessSystem chess = chessCreate();
     for(int i = 1; i < 10; i ++){
         assert(chessAddTournament(chess, i, 2000, "London") == CHESS_SUCCESS);
     }
     for(int i = 1; i < 10; i ++){
         for(int j = 1; j < 11; j ++) {
             assert(chessAddGame(chess, i, 12111, j, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
         }
     }
     chessDestroy(chess);
    FILE* file_levels = fopen("../tests/player_levels_your_output.txt", "w");
    ChessSystem chess2 = chessCreate();
    assert(chessAddTournament(chess2, 1, 2000, "London") == CHESS_SUCCESS);
    for(int i = 1; i < 10; i ++){
        assert(chessAddGame(chess2, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        assert(chessRemovePlayer(chess2, 1)==CHESS_SUCCESS);
    }
    assert(chessEndTournament(chess2, 1) == CHESS_SUCCESS);
//    char* our_path_level = "tests/player_levels_your_output.txt";
//    char* our_path_stats = "tests/tournament_statistics_your_output.txt";

   chessSavePlayersLevels(chess2, file_levels);
    assert(chessSaveTournamentStatistics(chess2, "../tests/tournament_statistics_your_output.txt") == CHESS_SUCCESS);
//    assert(compareFiles(our_path_stats, "../expected_files/stats/insane") == 1);
    fclose(file_levels);

//    assert(compareFiles(our_path_level, "../expected_files/level/insane") == 1);
    chessDestroy(chess2);

    // sort ranks test
    ChessSystem chess3 = chessCreate();
    assert(chessAddTournament(chess3, 1, 2000, "London") == CHESS_SUCCESS);
    for(int i = 1; i < 10; i++)
    {
        if (i < 100)
        {
            assert(chessAddGame(chess3,1, 12111, i, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
        if (i > 200 && i < 900)
        {
            assert(chessAddGame(chess3,1, i, i+1, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
        if (i > 900 && i < 950)
        {
            assert(chessAddGame(chess3,1, i+3, i+1, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
        }
    }
    for (int j = 1; j < 150; j++)
    {
        assert(chessAddGame(chess3,1, 1000, j, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    }
    file_levels = fopen("../tests/player_levels_your_output.txt", "w");
    assert(chessSavePlayersLevels(chess3, file_levels) == CHESS_SUCCESS);
    fclose(file_levels);
    chessDestroy(chess3);
    return true;
}

/*bool testChessRemovePlayer()
{
    ChessSystem chess = chessCreate();
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_TOURNAMENT_NOT_EXIST);
    assert(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 10, 20, DRAW, 2000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 20, 30, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 10, 30, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 30, 20, SECOND_PLAYER, 1000) == CHESS_GAME_ALREADY_EXISTS);
    assert(chessRemovePlayer(chess, 40) == CHESS_PLAYER_NOT_EXIST);
    assert(chessRemovePlayer(chess, 20) == CHESS_SUCCESS);
    assert(chessEndTournament(chess, 1) == CHESS_SUCCESS);
    assert(chessEndTournament(chess, 1) == CHESS_TOURNAMENT_ENDED);
    assert(chessEndTournament(chess, 2) == CHESS_TOURNAMENT_NOT_EXIST);

    chessDestroy(chess);
    return true;
}

bool testSaveTournamentStatistics()
{
    ChessSystem chess = chessCreate();
    assert(chessAddTournament(chess, 1, 4, "London") == CHESS_SUCCESS);
    assert(chessAddTournament(chess, 2, 10, "Tokyo") == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 10, 20, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 20, 30, FIRST_PLAYER, 1000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 20, 40, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 2, 50, 20, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 2, 50, 10, FIRST_PLAYER, 5000) == CHESS_SUCCESS);
    ChessResult error = CHESS_SUCCESS;
    assert(chessCalculateAveragePlayTime(chess, -20, &error) == 0);
    assert(error == CHESS_INVALID_ID);
    assert(chessCalculateAveragePlayTime(chess, 100, &error) == 0);
    assert(error == CHESS_PLAYER_NOT_EXIST);
    assert(chessCalculateAveragePlayTime(chess, 20, &error) == 2250);
    assert(error == CHESS_SUCCESS);
    assert(chessCalculateAveragePlayTime(chess, 10, &error) == 4000);
    assert(error == CHESS_SUCCESS);
    assert(chessCalculateAveragePlayTime(chess, 50, &error) == 3500);
    assert(error == CHESS_SUCCESS);
    assert(chessRemovePlayer(chess, 20) == CHESS_SUCCESS);
    assert(chessCalculateAveragePlayTime(chess, 20, &error) == 0);
    assert(error == CHESS_PLAYER_NOT_EXIST);
    chessDestroy(chess);
    return true;
}

bool testJunkValues()
{
    ChessSystem chess = chessCreate();
    assert(chessAddTournament(NULL, 1, 4, "London") == CHESS_NULL_ARGUMENT);
    assert(chessAddTournament(chess, 1, 4, NULL) == CHESS_NULL_ARGUMENT);
    assert(chessAddTournament(chess, -1, 4, "London") == CHESS_INVALID_ID);
    assert(chessAddTournament(chess, 1, -3, "London") == CHESS_INVALID_MAX_GAMES);
    assert(chessAddTournament(chess, 1, 4, "london") == CHESS_INVALID_LOCATION);
    assert(chessAddTournament(chess, 1, 4, "lOnd6n") == CHESS_INVALID_LOCATION);

    assert(chessAddTournament(chess, 1, 2, "Tel aviv") == CHESS_SUCCESS);
    assert(chessAddTournament(chess, 1, 2, "Tel aviv") == CHESS_TOURNAMENT_ALREADY_EXISTS);

    assert(chessAddGame(NULL, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_NULL_ARGUMENT);
    assert(chessAddGame(chess, -1, 1, 2, FIRST_PLAYER, 2000) == CHESS_INVALID_ID);
    assert(chessAddGame(chess, 1, -3, 2, FIRST_PLAYER, 2000) == CHESS_INVALID_ID);
    assert(chessAddGame(chess, 1, 1, -2, FIRST_PLAYER, 2000) == CHESS_INVALID_ID);
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, -2000) == CHESS_INVALID_PLAY_TIME);
    assert(chessAddGame(chess, 2, 1, 2, FIRST_PLAYER, 2000) == CHESS_TOURNAMENT_NOT_EXIST);
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 2000) == CHESS_GAME_ALREADY_EXISTS);
    assert(chessAddGame(chess, 1, 1, 3, FIRST_PLAYER, 2000) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 1, 4, FIRST_PLAYER, 2000) == CHESS_EXCEEDED_GAMES);
    assert(chessEndTournament(chess, 1) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 3, 4, FIRST_PLAYER, 2000) == CHESS_TOURNAMENT_ENDED);

    assert(chessRemoveTournament(NULL, 1) == CHESS_NULL_ARGUMENT);
    assert(chessRemoveTournament(chess, -5) == CHESS_INVALID_ID);
    assert(chessRemoveTournament(chess, 3) == CHESS_TOURNAMENT_NOT_EXIST);
    assert(chessRemoveTournament(chess, 1) == CHESS_SUCCESS);

    assert(chessAddGame(chess, 1, 1, 3, FIRST_PLAYER, 3000) == CHESS_TOURNAMENT_NOT_EXIST);

    assert(chessAddTournament(chess, 1, 1, "London") == CHESS_SUCCESS);
    assert(chessRemovePlayer(NULL, 1) == CHESS_NULL_ARGUMENT);
    assert(chessRemovePlayer(chess, -1) == CHESS_INVALID_ID);
    assert(chessRemovePlayer(chess, 1) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    assert(chessRemovePlayer(chess, 1) == CHESS_SUCCESS);

    assert(chessRemovePlayer(chess, 2) == CHESS_SUCCESS);
    assert(chessRemovePlayer(chess, 1) == CHESS_PLAYER_NOT_EXIST);
    assert(chessEndTournament(chess, 2) == CHESS_TOURNAMENT_NOT_EXIST);
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 3000) == CHESS_SUCCESS);
    assert(chessEndTournament(chess, 1) == CHESS_SUCCESS);
    assert(chessAddGame(chess, 1, 1, 2, FIRST_PLAYER, 3000) == CHESS_TOURNAMENT_ENDED);
    chessDestroy(chess);
    return true;
}*/