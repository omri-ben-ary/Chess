#ifndef CHESS_PROJECT_TOURNAMENT_H
#define CHESS_PROJECT_TOURNAMENT_H

#include "map.h"
#include "tournamentData.h"

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
 * @return
 *  TOURNAMENT_NULL_ARGUMENT if a NULL was sent as map or keyElement or dataElement
 * 	TOURNAMENT_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
 * 	an element or a key failed)
 * 	TOURNAMENT_SUCCESS the paired elements had been inserted successfully
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
 * @return
 *  TOURNAMENT_NULL_ARGUMENT if a NULL was sent to the function
 *  TOURNAMENT_DOES_NOT_EXIST if an equal key item does not already exists in the map
 * 	TOURNAMENT_SUCCESS the paired elements had been removed successfully
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
 * @param num_of_players_added - number of players added to the tournament in the game
 * @return
 *  TOURNAMENT_NULL_ARGUMENT if a NULL was sent as map or keyElement or dataElement
 * 	TOURNAMENT_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
 * 	an element or a key failed)
 * 	TOURNAMENT_SUCCESS the paired elements had been inserted successfully
 */
TournamentError tournamentTableAddGame(TournamentTable tournament_table, TournamentId tournament_id,
                                           int first_player, int second_player, GameResult winner, int play_time,
                                           int* num_of_players_added);

/**
 *
 * @param tournament_table - tournament table to address
 * @param tournament_id - tournament id to address
 * @param game_id - game id to address
 * @param player_id - player id to remove
 * @return
 *  TOURNAMENT_NULL_ARGUMENT if a NULL was sent to the function
 *  TOURNAMENT_DOES_NOT_EXIST if an equal key item does not already exists in the map
 * 	TOURNAMENT_SUCCESS the paired elements had been removed successfully
 */
TournamentError tournamentTableRemovePlayerInGame(TournamentTable tournament_table, TournamentId tournament_id,
                                               int game_id,int player_id);

/**
 *
 * @param tournament_table -tournament table to address
 * @param tournament_id - tournament to end
 * @return
 *  TOURNAMENT_OUT_OF_MEMORY if memory allocation failed
 *  TOURNAMENT_SUCCESS otherwise
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
 * @param path_file - the path of the output file
 * @return
 *  TOURNAMENT_SAVE_FAILURE if the file did not open properly or the fprintf failed
 *  TOURNAMENT_SUCCESS otherwise
 */
TournamentError tournamentTableGetStats(TournamentTable tournament_table, char* path_file);

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
