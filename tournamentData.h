#ifndef CHESS_PROJECT_TOURNAMENT_DATA_H
#define CHESS_PROJECT_TOURNAMENT_DATA_H

#include "game.h"

/**value type of map**/
typedef struct TournamentData_t *TournamentData;

/**
 *
 * @param location - name of the location the tournament takes place
 * @param max_games_per_player -max games allowed for a player to play in a tournament
 * @return if memory allocation failed NULL, otherwise tournament_data
 */
TournamentData tournamentDataCreate(const char* location, int max_games_per_player);

/**
 *
 * @param tournament_data - tournament data to destroy
 */
void tournamentDataDestroy(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to copy from
 * @return NULL if a memory allocation failed, otherwise a copy of tournament data
 */
TournamentData tournamentDataCopy(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - longest game time
 */
int tournamentDataGetLongestGame(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to update
 * @param longest_game_time - longest time to update
 */
void tournamentDataSetLongestGame(TournamentData tournament_data, int longest_game_time);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - average game time
 */
double tournamentDataGetAverageGameTime(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to update
 * @param game_time - game time of new game
 */
void tournamentDataSetAverageGameTime(TournamentData tournament_data, int new_game_time);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - max games allowed per player
 */
int tournamentDataGetMaxGames(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - tournament location name
 */
char* tournamentDataGetLocation(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - tournament game table
 */
GameTable tournamentDataGetGameTable(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - an unused game index
 */
int tournamentDataGetGameIndex(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to update
 */
void tournamentDataIncreaseGameIndex(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - id of tournament winner
 */
int tournamentDataGetWinnerId(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to update
 * @param winner_id - id of tournament winner
 */
void tournamentDataSetWinnerId(TournamentData tournament_data, int winner_id);

/**
 *
 * @param tournament_data - tournament data to take data from
 * @return - number of players in tournament
 */
int tournamentDataGetNumberOfPlayers(TournamentData tournament_data);

/**
 *
 * @param tournament_data - tournament data to update
 * @param num_of_players - number of players to set in tournament
 */
void tournamentDataSetNumberOfPlayers(TournamentData tournament_data, int num_of_players);

#endif //CHESS_PROJECT_TOURNAMENT_DATA_H
