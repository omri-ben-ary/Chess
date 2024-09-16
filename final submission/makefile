CC = gcc
OBJS = chess.o gameData.o game.o tournamentData.o tournament.o playerTournamentStats.o\
playerTournamentsMap.o playerStats.o playersMap.o
EXEC = chess
DEBUG_FLAG = -g -DNDEBUG
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror
$(EXEC) : $(OBJS)
	$(CC) -std=c99 $(OBJS) -o $@ tests/chessSystemTestsExample.c -L. libmap.a
chess.o : chessSystem.c chessSystem.h tournament.h  tournamentData.h game.h gameData.h\
playersMap.h playerStats.h playerTournamentsMap.h playerTournamentStats.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) chessSystem.c -o chess.o
tournament.o : tournament.c tournament.h tournamentData.h game.h gameData.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
tournamentData.o : tournamentData.c tournamentData.h game.h gameData.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
game.o : game.c game.h gameData.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
gameData.o : gameData.c gameData.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
playersMap.o : playersMap.c playersMap.h playerStats.h playerTournamentsMap.h playerTournamentStats.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
playerStats.o : playerStats.c playerStats.h playerTournamentsMap.h playerTournamentStats.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
playerTournamentsMap.o : playerTournamentsMap.c playerTournamentsMap.h playerTournamentStats.h map.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
playerTournamentStats.o : playerTournamentStats.c playerTournamentStats.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
clean:
	rm -f $(OBJS) $(EXEC)
