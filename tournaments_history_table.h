#ifndef MAIN_C_GAME_HISTORY_H
#define MAIN_C_GAME_HISTORY_H

#include "map.h"
#include "tournament_history.h"

typedef Map GamesHistory;
typedef int TournamentID;
typedef int GameID;

// games history map create
// games

/**
* gamesHistoryCreate: Allocates a new empty games history map.
* @return
* 	NULL - if one of the parameters is NULL or allocations failed.
* 	A new Map in case of success.
*/
GamesHistory gamesHistoryCreate();

/**
* gamesHistoryDestroy: Deallocates an existing map. Clears all elements by using the
* stored free functions.
* @param gameHistory - Target map to be deallocated. If map is NULL nothing will be done.
*/
void gamesHistoryDestroy(GamesHistory gamesHistory);

/**
* getNumberOfAttendedTournaments: Returns the number of elements in the games history map
* @param gamesHistory - The map which size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the number of elements in the map.
*/
int getNumberOfAttendedTournaments(GamesHistory gamesHistory);

/**
* isTournamentContained: Checks if a tournament element exists in the games history map.
* The tournament element will be considered in the player's games history
* if one of the tournament id's in the map is determined equal
* using the comparison function used to initialize the games history map.
*
* @param gamesHistory - The map to search in
* @param tournament_id - The element to look for. Will be compared using the
* 		comparison function.
* @return
* 	false - if one or more of the inputs is null, or if the player hasn't taken place in the tournament before
* 	true - if the player has already taken place in another game in the tournament before.
*/
bool isTournamentContained(GamesHistory gamesHistory, TournamentID tournament_id);

/**
*	mapPut: Gives a specified key a specific value.
*  Iterator's value is undefined after this operation.
*
* @param map - The map for which to reassign the data element
* @param keyElement - The key element which need to be reassigned
* @param dataElement - The new data element to associate with the given key.
*      A copy of the element will be inserted as supplied by the copying function
*      which is given at initialization and old data memory would be
*      deleted using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent as map or keyElement or dataElement
* 	MAP_OUT_OF_MEMORY if an allocation failed (Meaning the function for copying
* 	an element failed)
* 	MAP_SUCCESS the paired elements had been inserted successfully
*/
MapResult addOrEditTournamentHistory(GamesHistory gamesHistory,
                                       TournamentID tournament_id, TournamentData tournamentData);

/**
*	mapGet: Returns the data associated with a specific key in the map.
*			Iterator status unchanged
*
* @param map - The map for which to get the data element from.
* @param keyElement - The key element which need to be found and whos data
we want to get.
* @return
*  NULL if a NULL pointer was sent or if the map does not contain the requested key.
* 	The data element associated with the key otherwise.
*/
MapDataElement mapGet(Map map, MapKeyElement keyElement);

/**
* 	mapRemove: Removes a pair of key and data elements from the map. The elements
*  are found using the comparison function given at initialization. Once found,
*  the elements are removed and deallocated using the free functions
*  supplied at initialization.
*  Iterator's value is undefined after this operation.
*
* @param map -
* 	The map to remove the elements from.
* @param keyElement
* 	The key element to find and remove from the map. The element will be freed using the
* 	free function given at initialization. The data element associated with this key
*  will also be freed using the free function given at initialization.
* @return
* 	MAP_NULL_ARGUMENT if a NULL was sent to the function
*  MAP_ITEM_DOES_NOT_EXIST if an equal key item does not already exists in the map
* 	MAP_SUCCESS the paired elements had been removed successfully
*/
MapResult mapRemove(Map map, MapKeyElement keyElement);

/**
*	mapGetFirst: Sets the internal iterator (also called current key element) to
*	the smallest key element in the map and returns a copy of it. There doesn't
 *	need to be an internal order of the keys so the "first" key element is the
 *	smallest key available in the map. Use this to start iterating over the map.
*	To continue iteration use mapGetNext
*
* @param map - The map for which to set the iterator and return a copy of the first
* 		key element.
* @return
* 	NULL if a NULL pointer was sent or the map is empty or allocation fails
* 	The first key element of the map otherwise
*/
MapKeyElement mapGetFirst(Map map);

/**
*	mapGetNext: Advances the map iterator to the next key element and returns a copy of it.
*	The next key element is the smallest key element of the key elements that are
*   greater than the current key (key of the iterator).
* @param map - The map for which to advance the iterator
* @return
* 	NULL if reached the end of the map, or the iterator is at an invalid state
* 	,or a NULL sent as argument or allocation fails
* 	The next key element on the map in case of success
*/
MapKeyElement mapGetNext(Map map);


/**
* mapClear: Removes all key and data elements from target map.
* The elements are deallocated using the stored free functions.
* @param map
* 	Target map to remove all element from.
* @return
* 	MAP_NULL_ARGUMENT - if a NULL pointer was sent.
* 	MAP_SUCCESS - Otherwise.
*/
MapResult mapClear(Map map);

/*!
* Macro for iterating over a map.
* Declares a new iterator for the loop.
*/
#define MAP_FOREACH(type, iterator, map) \
    for(type iterator = (type) mapGetFirst(map) ; \
        iterator ;\
        iterator = mapGetNext(map))

#endif /* MAP_H_ */



#endif //MAIN_C_GAME_HISTORY_H
