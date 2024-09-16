#include "tournaments_history_table_tests.h"
#include "playerTournamentsMap.h"
#include <stdlib.h>
#include <stdio.h>

void test_of_tournament_history_table()
{
    PlayerTournamentStats tournament1_stats = playerTournamentStatsCreate(5);
    int tournament1_id = 208253559;
    PlayerTournamentsHistoryTable my_tournaments_history_table = playerTournamentsHistoryTableCreate();
    printf("is tournament 1 contained: %d (shouldn't be)\n", (MAP_SUCCESS == playerTournamentsHistoryTableContain(my_tournaments_history_table, tournament1_id)));
    printf("put tournament 1 result: %d\n",playerTournamentsHistoryTablePut(my_tournaments_history_table, tournament1_id, tournament1_stats));
    printf("is tournament 1 contained: %d (should be) d\n", MAP_SUCCESS == playerTournamentsHistoryTableContain(my_tournaments_history_table, tournament1_id));

    PlayerTournamentStats tournament2_stats = playerTournamentStatsCreate(2);
    int tournament2_id = 21234;
    printf("put tournament 2 result: %d\n",playerTournamentsHistoryTablePut(my_tournaments_history_table, tournament2_id, tournament2_stats));

    PlayerTournamentStats tournament3_stats = playerTournamentStatsCreate(3);
    int tournament3_id = 21236666; // what will happen when same id
    printf("put tournament 3 result: %d\n",playerTournamentsHistoryTablePut(my_tournaments_history_table, tournament3_id, tournament3_stats));

    PlayerTournamentStats tournament4_stats = playerTournamentStatsCreate(3);
    int tournament4_id = 21235;
    printf("put tournament 4 result: %d\n",playerTournamentsHistoryTablePut(my_tournaments_history_table, tournament4_id, tournament4_stats));
    printf("is tournament 1 contained: d (should be): %d\n", playerTournamentsHistoryTableContain(my_tournaments_history_table, tournament2_id));
    playerTournamentsHistoryTableRemove(my_tournaments_history_table, tournament2_id);
    printf("is tournament 1 contained: d (shouldn't be): %d\n", playerTournamentsHistoryTableContain(my_tournaments_history_table, tournament2_id));

    playerTournamentsHistoryTableAddGameStats(my_tournaments_history_table,tournament4_id, 123456);
    playerTournamentsHistoryTableAddGameStats(my_tournaments_history_table,tournament4_id, 123457);
    playerTournamentsHistoryTableAddGameStats(my_tournaments_history_table,tournament1_id, 111111);
    playerTournamentStatsDestroy(tournament1_stats);
    playerTournamentStatsDestroy(tournament2_stats);
    playerTournamentStatsDestroy(tournament3_stats);
    playerTournamentStatsDestroy(tournament4_stats);
    playerTournamentsHistoryTableDestroy(my_tournaments_history_table);
}