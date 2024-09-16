//
// Created by DELL on 19/05/2021.
//

#include "chessSystemTests.h"
#include "chessSystem.h"
#include <assert.h>

void tests_of_chess()
{
    // tests for chessCreate and chessDestroy
    ChessSystem chess = chessCreate();
    chessDestroy(chess);
    chess = chessCreate();
    chessDestroy(chess);

    chess = chessCreate();
    // tests for chessRemovePlayer
    // error checks:

    assert(chessRemovePlayer(NULL, 1234) == CHESS_NULL_ARGUMENT);
    assert(chessRemovePlayer(chess, 0) == CHESS_INVALID_ID);
    assert(chessRemovePlayer(chess, -5) == CHESS_INVALID_ID);
    assert(chessRemovePlayer(chess, 1) == CHESS_PLAYER_NOT_EXIST);

    // tests for chessCalculateAveragePlayTime
    // error checks:
    ChessResult chess_result = CHESS_SUCCESS;
    double d;
    d = chessCalculateAveragePlayTime(NULL, 1234, &chess_result);
    assert( chess_result == CHESS_NULL_ARGUMENT);
    d = chessCalculateAveragePlayTime(chess, 0, &chess_result);
    assert( chess_result == CHESS_INVALID_ID);
    d = chessCalculateAveragePlayTime(chess, -5, &chess_result);
    assert( chess_result == CHESS_INVALID_ID);
    d = chessCalculateAveragePlayTime(chess, 1, &chess_result);
    assert( chess_result == CHESS_PLAYER_NOT_EXIST);


    // tests for chessSavePlayersLevels
    // error checks:

    FILE* fd = fopen("C:\\Dell\\tmp_dir_for_chess\\tmp_file_for_chess.txt", "w");
    if (!fd)
    {
        return ;
    }
    assert(chessSavePlayersLevels(NULL,fd) == CHESS_NULL_ARGUMENT);
    assert(chessSavePlayersLevels(chess, NULL) == CHESS_NULL_ARGUMENT);
    fclose(fd);
    chessDestroy(chess);
}









