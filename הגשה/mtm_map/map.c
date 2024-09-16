#include "map.h"
#include "pair.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INITIAL_SIZE 10
#define EXPAND_FACTOR 2
#define ELEMENT_NOT_FOUND -1
#define UNDEFINED_SIZE -1
#define EMPTY_VAL 0
#define EVEN_DIVIDER 2
#define UNDEFINED_STATE -1

static MapResult mapCopyElements(Map map, MapDataElement dataElement, MapKeyElement keyElement, Pair* copyPair);
static void mapSwapNeighborElements(Map map, int index);
static void mapBubbleSort(Map map);
static MapResult mapExpandArrays(Map map);
static int mapFindKeyElementIndex(Map map, MapKeyElement keyElement);
static void mapShiftLeft(Map map, int index);

struct Map_t{
    Pair* pairs;
    int current_size;
    int maxSize;
    int iterator;
    copyMapDataElements copyDataElement;
    copyMapKeyElements copyKeyElement;
    freeMapDataElements freeDataElement;
    freeMapKeyElements freeKeyElement;
    compareMapKeyElements compareKeyElements;
};

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements)
{
    if ((copyDataElement == NULL) || (copyKeyElement == NULL) || (freeDataElement == NULL) ||
        (freeKeyElement == NULL) || (compareKeyElements == NULL))
    {
        return NULL;
    }

    Map map = malloc(sizeof(*map));
    if (map == NULL)
    {
        return NULL;
    }
    map->pairs = malloc(sizeof(Pair) * INITIAL_SIZE);
    if (map->pairs == NULL)
    {
        free(map);
        return NULL;
    }
    for (int i = 0 ; i<INITIAL_SIZE ; i++)
    {
        map->pairs[i].key = NULL;
        map->pairs[i].value = NULL;
    }

    map->maxSize = INITIAL_SIZE;
    map->current_size = EMPTY_VAL;
    map->iterator = UNDEFINED_STATE;
    map->copyDataElement = copyDataElement;
    map->copyKeyElement = copyKeyElement;
    map->freeDataElement = freeDataElement;
    map->freeKeyElement = freeKeyElement;
    map->compareKeyElements = compareKeyElements;
    return map;
}

static MapResult mapCopyElements(Map map, MapDataElement dataElement, MapKeyElement keyElement, Pair* copyPair)
{
    copyPair->value = map->copyDataElement(dataElement);
    if (copyPair->value == NULL)
    {
        return MAP_OUT_OF_MEMORY;
    }
    copyPair->key = map->copyKeyElement(keyElement);
    if (copyPair->key == NULL)
    {
        map->freeDataElement(copyPair->value);
        return MAP_OUT_OF_MEMORY;
    }
    return MAP_SUCCESS;
}

static void mapSwapNeighborElements(Map map, int index)
{
    int fixed_index = index-1;
    Pair tempPair = map->pairs[fixed_index];
    map->pairs[fixed_index] = map->pairs[index];
    map->pairs[index] = tempPair;
}

static void mapBubbleSort(Map map)
{
    int i = map->current_size++;
    while (i > 0)
    {
        int compare = map->compareKeyElements(map->pairs[i - 1].key, map->pairs[i].key);
        if (compare <= 0)
        {
            break;
        }
        mapSwapNeighborElements(map,i--);
    }
}

static MapResult mapExpandArrays(Map map)
{
    assert(map != NULL);
    int new_size = map->maxSize * EXPAND_FACTOR;
    Pair* expandedPairs= realloc(map->pairs,new_size*sizeof(Pair));
    if (expandedPairs == NULL)
    {
        return MAP_OUT_OF_MEMORY;
    }
    map->pairs = expandedPairs;
    map->maxSize = new_size;
    return MAP_SUCCESS;
}

static int mapFindKeyElementIndex(Map map, MapKeyElement keyElement)
{
    int low = 0, high = map->current_size - 1;
    if (high < 0)
    {
        return ELEMENT_NOT_FOUND;
    }
    while(low <= high)
    {
        int mid = (low+high) / EVEN_DIVIDER;
        int diff = map->compareKeyElements(map->pairs[mid].key,keyElement);
        if (diff == 0)
        {
            return mid;
        }
        else if (diff > 0)
        {
            high=mid-1;

        }
        else
        {
            low = mid+1;
        }
    }
    return ELEMENT_NOT_FOUND;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement)
{
    if (map == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    if(keyElement == NULL || dataElement == NULL)
    {
        map->iterator = UNDEFINED_STATE;
        return MAP_NULL_ARGUMENT;
    }
    Pair newPair = {NULL,NULL};

    if (mapCopyElements(map,dataElement,keyElement,&newPair) == MAP_OUT_OF_MEMORY)
    {
        map->iterator = UNDEFINED_STATE;
        return MAP_OUT_OF_MEMORY;
    }

    int keyElementIndex = mapFindKeyElementIndex(map,keyElement);
    if (keyElementIndex != ELEMENT_NOT_FOUND)
    {
        map->freeDataElement(map->pairs[keyElementIndex].value);
        map->freeKeyElement(newPair.key);
        map->pairs[keyElementIndex].value = newPair.value;
    }

    else
    {
        if (map->current_size == map->maxSize)
        {
            if (mapExpandArrays(map) == MAP_OUT_OF_MEMORY)
            {
                map->iterator = UNDEFINED_STATE;
                return MAP_OUT_OF_MEMORY;
            }
        }
        map->pairs[map->current_size] = newPair;
        mapBubbleSort(map);
    }
    map->iterator = UNDEFINED_STATE;
    return MAP_SUCCESS;
}

bool mapContains(Map map, MapKeyElement element)
{
    if (map == NULL)
    {
        return false;
    }
    if (element == NULL)
    {
        map->iterator = UNDEFINED_STATE;
        return false;
    }
    if (mapFindKeyElementIndex(map,element) == ELEMENT_NOT_FOUND)
    {
        map->iterator = UNDEFINED_STATE;
        return false;
    }
    map->iterator = UNDEFINED_STATE;
    return true;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement)
{
    if ((map == NULL) || (keyElement == NULL))
    {
        return NULL;
    }
    int elementIndex = mapFindKeyElementIndex(map,keyElement);
    if (elementIndex == ELEMENT_NOT_FOUND)
    {
        return NULL;
    }
    return map->pairs[elementIndex].value;
}

static void mapShiftLeft(Map map, int index)
{
    if (map->current_size == EMPTY_VAL)
    {
        return;
    }
    int end = map->current_size--;
    for (int i = index+1 ; i<end ; i++)
    {
        map->pairs[i-1]= map->pairs[i];
    }
    map->pairs[end-1].key = NULL;
    map->pairs[end-1].value = NULL;
}

MapResult mapRemove(Map map, MapKeyElement keyElement)
{
    if (map == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    if (keyElement == NULL)
    {
        map->iterator = UNDEFINED_STATE;
        return MAP_NULL_ARGUMENT;
    }
    int indexToRemove = mapFindKeyElementIndex(map,keyElement);
    if (indexToRemove == ELEMENT_NOT_FOUND)
    {
        map->iterator = UNDEFINED_STATE;
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    map->freeKeyElement(map->pairs[indexToRemove].key);
    map->freeDataElement(map->pairs[indexToRemove].value);
    mapShiftLeft(map,indexToRemove);

    map->iterator = UNDEFINED_STATE;
    return MAP_SUCCESS;
}

int mapGetSize(Map map)
{
    if (map == NULL)
    {
        return UNDEFINED_SIZE;
    }

    return map->current_size;
}

MapResult mapClear(Map map)
{
    if (map == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    for (int i=map->current_size-1 ; i>=0 ; i--)
    {
        mapRemove(map,map->pairs[i].key);
    }
    return MAP_SUCCESS;
}

void mapDestroy(Map map)
{
    if (map == NULL)
    {
        return;
    }
    mapClear(map);
    map->freeKeyElement(map->pairs);
    free(map);
}

Map mapCopy(Map map)
{
    if (map == NULL)
    {
        return NULL;
    }
    Map copyOfMap = mapCreate(map->copyDataElement, map->copyKeyElement, map->freeDataElement,
                              map->freeKeyElement, map->compareKeyElements);
    if (copyOfMap == NULL)
    {
        map->iterator = UNDEFINED_STATE;
        return NULL;
    }
    for (int i = 0; i < map->current_size ; i++)
    {
        mapPut(copyOfMap, map->pairs[i].key, map->pairs[i].value);
    }
    map->iterator = UNDEFINED_STATE;
    return copyOfMap;
}

MapKeyElement mapGetFirst(Map map)
{
    if ((map == NULL) || (map->current_size == EMPTY_VAL))
    {
        return NULL;
    }
    map->iterator = 0;
    return mapGetNext(map);
}

MapKeyElement mapGetNext(Map map)
{
    if ((map == NULL) || (map->iterator == UNDEFINED_STATE) || (map->iterator >= map->current_size))
    {
        return NULL;
    }
    return map->copyKeyElement(map->pairs[map->iterator++].key);
}
