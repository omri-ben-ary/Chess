# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/omri/mtm/ex1/chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1

# Include any dependencies generated for this target.
include CMakeFiles/chess_project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chess_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chess_project.dir/flags.make

CMakeFiles/chess_project.dir/mainOmri.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/mainOmri.c.o: ../mainOmri.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/chess_project.dir/mainOmri.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/mainOmri.c.o   -c /home/omri/mtm/ex1/chess/mainOmri.c

CMakeFiles/chess_project.dir/mainOmri.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/mainOmri.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/mainOmri.c > CMakeFiles/chess_project.dir/mainOmri.c.i

CMakeFiles/chess_project.dir/mainOmri.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/mainOmri.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/mainOmri.c -o CMakeFiles/chess_project.dir/mainOmri.c.s

CMakeFiles/chess_project.dir/game_tests.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/game_tests.c.o: ../game_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/chess_project.dir/game_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/game_tests.c.o   -c /home/omri/mtm/ex1/chess/game_tests.c

CMakeFiles/chess_project.dir/game_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/game_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/game_tests.c > CMakeFiles/chess_project.dir/game_tests.c.i

CMakeFiles/chess_project.dir/game_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/game_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/game_tests.c -o CMakeFiles/chess_project.dir/game_tests.c.s

CMakeFiles/chess_project.dir/game.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/game.c.o: ../game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/chess_project.dir/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/game.c.o   -c /home/omri/mtm/ex1/chess/game.c

CMakeFiles/chess_project.dir/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/game.c > CMakeFiles/chess_project.dir/game.c.i

CMakeFiles/chess_project.dir/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/game.c -o CMakeFiles/chess_project.dir/game.c.s

CMakeFiles/chess_project.dir/gamedata.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/gamedata.c.o: ../gamedata.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/chess_project.dir/gamedata.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/gamedata.c.o   -c /home/omri/mtm/ex1/chess/gamedata.c

CMakeFiles/chess_project.dir/gamedata.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/gamedata.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/gamedata.c > CMakeFiles/chess_project.dir/gamedata.c.i

CMakeFiles/chess_project.dir/gamedata.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/gamedata.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/gamedata.c -o CMakeFiles/chess_project.dir/gamedata.c.s

CMakeFiles/chess_project.dir/map.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/map.c.o: ../map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/chess_project.dir/map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/map.c.o   -c /home/omri/mtm/ex1/chess/map.c

CMakeFiles/chess_project.dir/map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/map.c > CMakeFiles/chess_project.dir/map.c.i

CMakeFiles/chess_project.dir/map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/map.c -o CMakeFiles/chess_project.dir/map.c.s

CMakeFiles/chess_project.dir/tournament.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/tournament.c.o: ../tournament.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/chess_project.dir/tournament.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/tournament.c.o   -c /home/omri/mtm/ex1/chess/tournament.c

CMakeFiles/chess_project.dir/tournament.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/tournament.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/tournament.c > CMakeFiles/chess_project.dir/tournament.c.i

CMakeFiles/chess_project.dir/tournament.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/tournament.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/tournament.c -o CMakeFiles/chess_project.dir/tournament.c.s

CMakeFiles/chess_project.dir/tournamentdata.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/tournamentdata.c.o: ../tournamentdata.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/chess_project.dir/tournamentdata.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/tournamentdata.c.o   -c /home/omri/mtm/ex1/chess/tournamentdata.c

CMakeFiles/chess_project.dir/tournamentdata.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/tournamentdata.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/tournamentdata.c > CMakeFiles/chess_project.dir/tournamentdata.c.i

CMakeFiles/chess_project.dir/tournamentdata.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/tournamentdata.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/tournamentdata.c -o CMakeFiles/chess_project.dir/tournamentdata.c.s

CMakeFiles/chess_project.dir/tournament_tests.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/tournament_tests.c.o: ../tournament_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/chess_project.dir/tournament_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/tournament_tests.c.o   -c /home/omri/mtm/ex1/chess/tournament_tests.c

CMakeFiles/chess_project.dir/tournament_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/tournament_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/tournament_tests.c > CMakeFiles/chess_project.dir/tournament_tests.c.i

CMakeFiles/chess_project.dir/tournament_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/tournament_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/tournament_tests.c -o CMakeFiles/chess_project.dir/tournament_tests.c.s

CMakeFiles/chess_project.dir/player_stats.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/player_stats.c.o: ../player_stats.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/chess_project.dir/player_stats.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/player_stats.c.o   -c /home/omri/mtm/ex1/chess/player_stats.c

CMakeFiles/chess_project.dir/player_stats.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/player_stats.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/player_stats.c > CMakeFiles/chess_project.dir/player_stats.c.i

CMakeFiles/chess_project.dir/player_stats.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/player_stats.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/player_stats.c -o CMakeFiles/chess_project.dir/player_stats.c.s

CMakeFiles/chess_project.dir/tournament_history.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/tournament_history.c.o: ../tournament_history.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/chess_project.dir/tournament_history.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/tournament_history.c.o   -c /home/omri/mtm/ex1/chess/tournament_history.c

CMakeFiles/chess_project.dir/tournament_history.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/tournament_history.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/tournament_history.c > CMakeFiles/chess_project.dir/tournament_history.c.i

CMakeFiles/chess_project.dir/tournament_history.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/tournament_history.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/tournament_history.c -o CMakeFiles/chess_project.dir/tournament_history.c.s

CMakeFiles/chess_project.dir/tournaments_history_table.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/tournaments_history_table.c.o: ../tournaments_history_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/chess_project.dir/tournaments_history_table.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/tournaments_history_table.c.o   -c /home/omri/mtm/ex1/chess/tournaments_history_table.c

CMakeFiles/chess_project.dir/tournaments_history_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/tournaments_history_table.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/tournaments_history_table.c > CMakeFiles/chess_project.dir/tournaments_history_table.c.i

CMakeFiles/chess_project.dir/tournaments_history_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/tournaments_history_table.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/tournaments_history_table.c -o CMakeFiles/chess_project.dir/tournaments_history_table.c.s

CMakeFiles/chess_project.dir/players_map.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/players_map.c.o: ../players_map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/chess_project.dir/players_map.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/players_map.c.o   -c /home/omri/mtm/ex1/chess/players_map.c

CMakeFiles/chess_project.dir/players_map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/players_map.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/players_map.c > CMakeFiles/chess_project.dir/players_map.c.i

CMakeFiles/chess_project.dir/players_map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/players_map.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/players_map.c -o CMakeFiles/chess_project.dir/players_map.c.s

CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.o: ../tournaments_history_table_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.o   -c /home/omri/mtm/ex1/chess/tournaments_history_table_tests.c

CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/tournaments_history_table_tests.c > CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.i

CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/tournaments_history_table_tests.c -o CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.s

CMakeFiles/chess_project.dir/players_map_tests.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/players_map_tests.c.o: ../players_map_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/chess_project.dir/players_map_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/players_map_tests.c.o   -c /home/omri/mtm/ex1/chess/players_map_tests.c

CMakeFiles/chess_project.dir/players_map_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/players_map_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/players_map_tests.c > CMakeFiles/chess_project.dir/players_map_tests.c.i

CMakeFiles/chess_project.dir/players_map_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/players_map_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/players_map_tests.c -o CMakeFiles/chess_project.dir/players_map_tests.c.s

CMakeFiles/chess_project.dir/chessSystem.c.o: CMakeFiles/chess_project.dir/flags.make
CMakeFiles/chess_project.dir/chessSystem.c.o: ../chessSystem.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/chess_project.dir/chessSystem.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/chess_project.dir/chessSystem.c.o   -c /home/omri/mtm/ex1/chess/chessSystem.c

CMakeFiles/chess_project.dir/chessSystem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/chess_project.dir/chessSystem.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/omri/mtm/ex1/chess/chessSystem.c > CMakeFiles/chess_project.dir/chessSystem.c.i

CMakeFiles/chess_project.dir/chessSystem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/chess_project.dir/chessSystem.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/omri/mtm/ex1/chess/chessSystem.c -o CMakeFiles/chess_project.dir/chessSystem.c.s

# Object files for target chess_project
chess_project_OBJECTS = \
"CMakeFiles/chess_project.dir/mainOmri.c.o" \
"CMakeFiles/chess_project.dir/game_tests.c.o" \
"CMakeFiles/chess_project.dir/game.c.o" \
"CMakeFiles/chess_project.dir/gamedata.c.o" \
"CMakeFiles/chess_project.dir/map.c.o" \
"CMakeFiles/chess_project.dir/tournament.c.o" \
"CMakeFiles/chess_project.dir/tournamentdata.c.o" \
"CMakeFiles/chess_project.dir/tournament_tests.c.o" \
"CMakeFiles/chess_project.dir/player_stats.c.o" \
"CMakeFiles/chess_project.dir/tournament_history.c.o" \
"CMakeFiles/chess_project.dir/tournaments_history_table.c.o" \
"CMakeFiles/chess_project.dir/players_map.c.o" \
"CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.o" \
"CMakeFiles/chess_project.dir/players_map_tests.c.o" \
"CMakeFiles/chess_project.dir/chessSystem.c.o"

# External object files for target chess_project
chess_project_EXTERNAL_OBJECTS =

chess_project: CMakeFiles/chess_project.dir/mainOmri.c.o
chess_project: CMakeFiles/chess_project.dir/game_tests.c.o
chess_project: CMakeFiles/chess_project.dir/game.c.o
chess_project: CMakeFiles/chess_project.dir/gamedata.c.o
chess_project: CMakeFiles/chess_project.dir/map.c.o
chess_project: CMakeFiles/chess_project.dir/tournament.c.o
chess_project: CMakeFiles/chess_project.dir/tournamentdata.c.o
chess_project: CMakeFiles/chess_project.dir/tournament_tests.c.o
chess_project: CMakeFiles/chess_project.dir/player_stats.c.o
chess_project: CMakeFiles/chess_project.dir/tournament_history.c.o
chess_project: CMakeFiles/chess_project.dir/tournaments_history_table.c.o
chess_project: CMakeFiles/chess_project.dir/players_map.c.o
chess_project: CMakeFiles/chess_project.dir/tournaments_history_table_tests.c.o
chess_project: CMakeFiles/chess_project.dir/players_map_tests.c.o
chess_project: CMakeFiles/chess_project.dir/chessSystem.c.o
chess_project: CMakeFiles/chess_project.dir/build.make
chess_project: CMakeFiles/chess_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C executable chess_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chess_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chess_project.dir/build: chess_project

.PHONY : CMakeFiles/chess_project.dir/build

CMakeFiles/chess_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chess_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chess_project.dir/clean

CMakeFiles/chess_project.dir/depend:
	cd /home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/omri/mtm/ex1/chess /home/omri/mtm/ex1/chess /home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1 /home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1 /home/omri/mtm/ex1/chess/cmake-build-debug-remote-host-1/CMakeFiles/chess_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chess_project.dir/depend

