#ifndef CHESS_PROJECT_TOURNAMENT_H
#define CHESS_PROJECT_TOURNAMENT_H

#include "map.h"
#include "tournamentdata.h"

#define MIN_LOSE_INIT (-1)
#define PLAYER_WIN 0
#define PLAYER_LOSE 1
#define PLAYER_DRAW 2
/**TournamentTable is of map data type**/
typedef Map TournamentTable;

/**Key type of map, a positive int**/
typedef int TournamentId;

/**Error codes that occur when using Tournament data type**/
typedef enum TournamentErrorCode_t{
    TOURNAMENT_NULL_ARGUMENT,
    TOURNAMENT_OUT_OF_MEMORY,
    TOURNAMENT_DOES_NOT_EXIST,
    TOURNAMENT_SAVE_FAILURE,
    TOURNAMENT_SUCCESS
}TournamentError;

/********************************************Functions*****************************************************/

/**
 *
 * @return NULL if memory allocation failed
 *         otherwise returns a tournament table
 */
TournamentTable tournamentTableCreate();

/**
 *
 * @param tournament_table - tournament table to be destroyed
 */
void tournamentTableDestroy(TournamentTable tournament_table);

/**
 *
 * @param tournament_table - tournament to check in
 * @param tournament_id - tournament id to look for
 * @return true if it's contained and false if not
 */
bool tournamentTableContains(TournamentTable tournament_table, TournamentId tournament_id);

/**
 *
 * @param tournament_table - tournament table to add to
 * @param tournament_id - tournament id of tournament
 * @param tournament_data - tournament data of tournament
 * @return Map error codes
 */
TournamentError tournamentTableAddOrEditTournament(TournamentTable tournament_table, TournamentId tournament_id,
                                        TournamentData tournament_data);

/**
 *
 * @param tournament_table - tournament table to retrieve data from
 * @param tournament_id - tournament id to retrieve data from
 * @return tournament's data
 */
TournamentData tournamentTableGetTournamentData(TournamentTable tournament_table, TournamentId tournament_id);

/**
 *
 * @param tournament_table - tournament table in which the wanted tournament is found
 * @param tournament_id - tournament id to remove
 * @return Map error codes
 */
TournamentError tournamentTableDeleteTournament(TournamentTable tournament_table, TournamentId tournament_id);

/**
 *
 * @param tournament_table - tournament table to add game to
 * @param tournament_id - tournament id to add game to
 * @param first_player - id of first player
 * @param second_player - id of second player
 * @param winner - enum of the winner
 * @param play_time - play time of the game
 * @return Map error codes
 */
TournamentError tournamentTableAddGame(TournamentTable tournament_table, TournamentId tournament_id,
                                           int first_player, int second_player, GameResult winner, int play_time);

/**
 *
 * @param tournament_table - tournament table to address
 * @param tournament_id - tournament id to address
 * @param game_id - game id to address
 * @param player_id - player id to remove
 * @return Map error codes
 */
TournamentError tournamentTableRemovePlayerInGame(TournamentTable tournament_table, TournamentId tournament_id,
                                               int game_id,int player_id);

/**
 *
 * @param tournament_table -tournament table to address
 * @param tournament_id - tournament to end
 * @return Map error codes
 */
TournamentError tournamentTableEndTournament(TournamentTable tournament_table, TournamentId tournament_id);

/**
 *
 * @param tournament_table - tournament table to address
 * @param tournament_id - tournament id to address
 * @param game_id -game id to address
 * @return game time of game
 */
int tournamentTableGetGameTime(TournamentTable tournament_table, TournamentId tournament_id, int game_id);

/**
 *
 * @param tournament_table - tournament table in which tournament id is found
 * @param tournament_id - tournament id to calculate stats
 * @param path_file - the path of the output file
 * @return Map error codes
 */
TournamentError tournamentTableGetStatsOfTournament(TournamentTable tournament_table, char* path_file);

/**
 *
 * @param tournament_table - tournament table to look in
 * @param tournament_id - tournament id in which game is found
 * @param game_id - game id wo check in
 * @param player_id - player to check result
 * @return PLAYER_WIN if player won, PLAYER_LOSE if player lost, PLAYER_DRAW if the result is draw
 */
int tournamentTableGetPlayerResultInGame(TournamentTable tournament_table, TournamentId tournament_id, int game_id,
                                 int player_id);

#endif //CHESS_PROJECT_TOURNAMENT_H
