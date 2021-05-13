#include "tournaments_history_table_tests.h"
#include "tournaments_history_table.h"
#include "stdio.h"
#include "stdlib.h"


void test_of_tournament_history_table()
{
    TournamentStats tournament1_stats = tournamentStatsCreate(5);
    int tournament1_id = 208253559;
    TournamentsHistoryTable my_tournaments_history_table = tournamentsHistoryTableCreate();
    printf("is tournament 1 contained: %d (shouldn't be)\n", (MAP_SUCCESS == isTournamentContained(my_tournaments_history_table, tournament1_id)));
    printf("put tournament 1 result: %d\n",tournamentStatsPut(my_tournaments_history_table, tournament1_id, tournament1_stats));
    printf("is tournament 1 contained: %d (should be) d\n", MAP_SUCCESS == isTournamentContained(my_tournaments_history_table, tournament1_id));

    TournamentStats tournament2_stats = tournamentStatsCreate(2);
    int tournament2_id = 21234;
    printf("put tournament 2 result: %d\n",tournamentStatsPut(my_tournaments_history_table, tournament2_id, tournament2_stats));

    TournamentStats tournament3_stats = tournamentStatsCreate(3);
    int tournament3_id = 21236666; // what will happen when same id
    printf("put tournament 3 result: %d\n",tournamentStatsPut(my_tournaments_history_table, tournament3_id, tournament3_stats));

    TournamentStats tournament4_stats = tournamentStatsCreate(3);
    int tournament4_id = 21235;
    printf("put tournament 4 result: %d\n",tournamentStatsPut(my_tournaments_history_table, tournament4_id, tournament4_stats));
    printf("is tournament 1 contained: d (should be): %d\n", isTournamentContained(my_tournaments_history_table, tournament2_id));
    tournamentHistoryRemove(my_tournaments_history_table, tournament2_id);
    printf("is tournament 1 contained: d (shouldn't be): %d\n", isTournamentContained(my_tournaments_history_table, tournament2_id));

    addGameStatsToTournamentStats(my_tournaments_history_table,tournament4_id, 123456);
    addGameStatsToTournamentStats(my_tournaments_history_table,tournament4_id, 123457);
    addGameStatsToTournamentStats(my_tournaments_history_table,tournament1_id, 111111);

    MAP_FOREACH (int * ,id, my_tournaments_history_table)
    {
        TournamentStats current_tournament = tournamentStatsGet(my_tournaments_history_table,*id);
        printf("tournament id: %d, max games allowed: %d\n", *id, maxGamesAllowedGet(current_tournament));
        free(id);
    }
    tournamentStatsDestroy(tournament1_stats);
    tournamentStatsDestroy(tournament2_stats);
    tournamentStatsDestroy(tournament3_stats);
    tournamentStatsDestroy(tournament4_stats);
    tournamentsHistoryTableDestroy(my_tournaments_history_table);
}