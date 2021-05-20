#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define INITIAL_MAP_MAX_SIZE 5

#define INVALID_ITERATOR -1
#define EXPAND_FACTOR 2


// binary search possible errors
typedef enum {
    SEARCH_SUCCESS = 0,
    SEARCH_FAILED=-1,
    ITEM_NOT_FOUND=-2,
} SearchResults;

typedef enum {
    RESIZE_SUCCESS = 0,
    RESIZE_OUT_OF_MEMORY,
    // you set resize null argument to 0 which mean no need was 1 and out of memory was 1
    RESIZE_NULL_ARGUMENT,
    NO_NEED_FOR_RESIZE,
}  ResizeResult;

// struct representing a key value pair in a map
typedef struct KeyValuePair {
    MapKeyElement key;
    MapDataElement value;

} *KeyValuePair;

// struct representing a map
struct Map_t {
    KeyValuePair *key_value_pairs;
    int current_size;
    int max_size;
    int iterator;
    // function pointers
    MapDataElement(*copyData)(MapDataElement);
    MapKeyElement(*copyKey)(MapKeyElement);
    void(*freeData)(MapDataElement);
    void(*freeKey)(MapKeyElement);
    int(*compareKeys)(MapKeyElement, MapKeyElement);
};

// function declarations not included in header file
static int getSortedIndex(Map map, MapKeyElement key, SearchResults *error_code);
static KeyValuePair pairCreate(Map map, MapKeyElement key, MapDataElement value);
// moves all elements from index to the right
static void shiftArrayRight(Map map, int index);
// moves all elements of array from index to the left
static void shiftArrayLeft(Map map, int index);
// frees a pair struct
static void freePair(Map map, KeyValuePair pair);
// checks if size is too small to add another and if yes resizes
static ResizeResult checkResize(Map map);
// copies pair struct
static KeyValuePair pairCopy(Map map, KeyValuePair pair);
// updates indices for binary search
static void updateIndices(int key_comparison, int *index, int *low, int *high);
// get pair from map
static KeyValuePair getPair(Map map, int index);
// get key from pair
static MapKeyElement getKey(KeyValuePair pair);
// get data from pair
static MapKeyElement getData(KeyValuePair pair);
// gets current max size of map
static int mapGetMaxSize(Map map);
// checks if iterator is invalid size
static int mapIsIteratorValid(Map map);
// set iterator to invalid
static void mapSetIteratorInvalid(Map map);
// checks whether to add the element to left of location or right
static int AddLeftOrRight(Map map, int index, MapKeyElement key);
// add new pair to map
static MapResult addNewPair(Map map, MapKeyElement key, MapDataElement data, int index);
static ResizeResult resize(Map map);
// writes over an existing pair's value
static bool changePairValue(Map map, KeyValuePair pair, MapDataElement value);
// sets a pairs value
static bool setData(Map map, KeyValuePair pair, MapDataElement value);
// sets a pairs key
static bool setKey(Map map, KeyValuePair pair, MapKeyElement key);
// function implementations
static KeyValuePair pairCopy(Map map, KeyValuePair pair){
    KeyValuePair new_pair = pairCreate(map, getKey(pair), getData(pair));
    return new_pair;
}
static bool setData(Map map, KeyValuePair pair, MapDataElement value)
{
    MapDataElement new_data = map->copyData(value);
    if(new_data==NULL){
        return false;
    }
    pair->value= new_data;
    return true;

}
static bool setKey(Map map, KeyValuePair pair, MapKeyElement key)
{
    MapKeyElement new_key = map->copyKey(key);
    if(new_key==NULL){
        return false;
    }
    pair->key= new_key;
    return true;
}
static bool changePairValue(Map map, KeyValuePair pair, MapDataElement value)
{
    MapDataElement old_data = getData(pair);
    if(!setData(map, pair, value)){
        return false;
    }
    map->freeData(old_data);
    return true;
}
KeyValuePair pairCreate(Map map, MapKeyElement key, MapDataElement value)
{
    KeyValuePair new_pair = malloc(sizeof(*new_pair));
    // check if allocation successful
    if(new_pair == NULL){
        return NULL;
    }
    if(!setKey(map, new_pair, key) || !setData(map, new_pair, value)){
        freePair(map, new_pair);
        return NULL;
    }
    return new_pair;
}


// map functions
Map mapCreate(copyMapDataElements copyDataElement, copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement, freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements)
{
    // check if one of the parameters is null
    if(copyDataElement==NULL || copyKeyElement==NULL || freeDataElement==NULL ||
       freeKeyElement==NULL || compareKeyElements==NULL){
        return NULL;
    }
    Map new_map = malloc(sizeof(*new_map));
    // check if memory allocation succeeded
    if(new_map == NULL){
        return NULL;
    }
    // set values
    new_map->current_size = 0;
    new_map->max_size = INITIAL_MAP_MAX_SIZE;
    new_map->iterator = 0;
    new_map->key_value_pairs = malloc(sizeof(KeyValuePair)*INITIAL_MAP_MAX_SIZE);
    // check if allocation succeeded
    if(new_map->key_value_pairs==NULL){
        free(new_map);
        return NULL;
    }
    // init functions
    new_map->copyData = copyDataElement;
    new_map->copyKey = copyKeyElement;
    new_map->freeData = freeDataElement;
    new_map->freeKey = freeKeyElement;
    new_map->compareKeys = compareKeyElements;
    return new_map;
}

Map mapCopy(Map map)
{
    // if was sent null
    if(map == NULL){
        return NULL;
    }
    // allocate memory for new map
    Map new_map = malloc(sizeof(*map));
    // check if allocation successful
    if(new_map == NULL){
        return NULL;
    }
    // copy key value pairs
    int key_value_pair_size = sizeof(struct KeyValuePair)*mapGetMaxSize(map);
    KeyValuePair *new_pairs = malloc(key_value_pair_size);
    if(new_pairs == NULL){
        free(new_map);
        return NULL;
    }
    // copy pairs
    for(int i = 0; i < mapGetSize(map); i++){
        new_pairs[i] = pairCopy(map, getPair(map, i));
    }
    // set iterators to invalid
    mapSetIteratorInvalid(map);
    memcpy(new_map, map, sizeof(*map));
    // change the key value pairs to new ones
    new_map->key_value_pairs = new_pairs;
    return new_map;
}

void mapPrint(Map map)
{
    printf("max_size: %d\n", map->max_size);
    printf("current_size: %d\n", map->current_size);
    printf("iterator: %d\n", map->iterator);
    for(int i = 0; i < map->current_size; i++){
        printf("key: %d  ", *(int *)(map->key_value_pairs[i]->key));
        printf("value: %c value as int: %d\n",*(char*)(map->key_value_pairs[i]->value),
               *(char*)(map->key_value_pairs[i]->value));
    }
}
static int AddLeftOrRight(Map map, int index, MapKeyElement key)
{
    KeyValuePair pair = getPair(map, index);
    MapKeyElement current_key = getKey(pair);
    int key_comparison = map->compareKeys(current_key, key);
    return (key_comparison<0)*1;
}
static MapResult addNewPair(Map map, MapKeyElement key, MapDataElement data, int index)
{
    // create new pair
    KeyValuePair new_pair = pairCreate(map, key, data);
    if(new_pair==NULL){
        return MAP_OUT_OF_MEMORY;
    }
    shiftArrayRight(map, index);
    map->key_value_pairs[index] = new_pair;
    // increment array size
    map->current_size++;
    return MAP_SUCCESS;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement)
{
    // check if map is null
    if ( map==NULL || keyElement == NULL || dataElement == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    // check that size is ok and if not resize
    ResizeResult result = checkResize(map);
    if(result==RESIZE_OUT_OF_MEMORY){
        return MAP_OUT_OF_MEMORY;
    }
    if(mapGetSize(map)==0){
        if(addNewPair(map, keyElement, dataElement, 0) == MAP_OUT_OF_MEMORY){
            return MAP_OUT_OF_MEMORY;
        }else{
            return MAP_SUCCESS;
        }
    }
    SearchResults error_code = SEARCH_SUCCESS;
    int index = getSortedIndex(map, keyElement, &error_code);
    if(error_code==SEARCH_FAILED){
        return MAP_OUT_OF_MEMORY;
    }
    // item not found
    if(error_code==ITEM_NOT_FOUND){
        // check if to add to left of index or right
        int shifted_index = index + AddLeftOrRight(map, index, keyElement);
        if(addNewPair(map, keyElement, dataElement, shifted_index) == MAP_OUT_OF_MEMORY){
            return MAP_OUT_OF_MEMORY;
        }
    }
    // found item
    if(error_code==SEARCH_SUCCESS){
        // change value of Pair at index found
        KeyValuePair pair = getPair(map, index);
        if(!changePairValue(map, pair, dataElement)){
            return MAP_OUT_OF_MEMORY;
        }

    }
    // set iterator to invalid
    mapSetIteratorInvalid(map);
    return MAP_SUCCESS;
}
static void freePair(Map map, KeyValuePair pair)
{
    map->freeKey(pair->key);
    map->freeData(pair->value);
    free(pair);
}
MapResult mapRemove(Map map, MapKeyElement keyElement)
{
    if(map==NULL || keyElement==NULL){
        return MAP_NULL_ARGUMENT;
    }
    SearchResults result = SEARCH_SUCCESS;
    int index = getSortedIndex(map, keyElement, &result);
    if(result==SEARCH_FAILED){
        return MAP_NULL_ARGUMENT;
    }
    if(result == ITEM_NOT_FOUND){
        return MAP_ITEM_DOES_NOT_EXIST;
    }
    KeyValuePair pair = map->key_value_pairs[index];
    freePair(map, pair);
    shiftArrayLeft(map, index);
    // set iterator to invalid state
    mapSetIteratorInvalid(map);
    // decrease size
    map->current_size--;
    return MAP_SUCCESS;

}

MapKeyElement mapGetFirst(Map map)
{
    // check if map empty or null
    if(map==NULL || mapGetSize(map)==0){
        return NULL;
    }
    // set iterator to 0
    map->iterator=0;
    // return first pair data
    KeyValuePair pair = getPair(map, map->iterator);
    return map->copyKey(getKey(pair));
}

MapKeyElement mapGetNext(Map map)
{
    // check if map empty or null
    if(map==NULL || map->iterator+1==mapGetSize(map) || !mapIsIteratorValid(map)){
        return NULL;
    }
    // increment iterator
    map->iterator++;
    // return data at index of iterators value
    KeyValuePair pair = getPair(map, map->iterator);
    return map->copyKey(getKey(pair));
}
static int getSortedIndex(Map map, MapKeyElement key, SearchResults *error_code){
    if(map == NULL){
        *error_code = SEARCH_FAILED;
        return SEARCH_FAILED;
    }
    int low = 0;
    int high = map->current_size -1;
    int index = (high + low)/2;
    while(low <= high){

        KeyValuePair pair = getPair(map, index);
        MapKeyElement current_key = getKey(pair);
        int key_comparison = map->compareKeys(current_key, key);
        // if key is equivalent
        if(key_comparison == 0){
            *error_code=SEARCH_SUCCESS;
            return index;
        }
        updateIndices(key_comparison, &index, &low, &high);
    }
    // did not find
    *error_code=ITEM_NOT_FOUND;
    return index;
}

static void updateIndices(int key_comparison, int *index, int *low, int *high)
{
    // check if key at index is lower than current key
    if(key_comparison > 0){
        *high = *index -1;
    }else{
        *low = *index +1;
    }
    *index =  (*high + *low)/2;

}
static int mapIsIteratorValid(Map map)
{
    if(map->iterator==INVALID_ITERATOR){
        return 0;
    }
    return 1;
}
static KeyValuePair getPair(Map map, int index)
{
    return map->key_value_pairs[index];
}

static int mapGetMaxSize(Map map)
{
    return map->max_size;
}

void incrementSize(Map map)
{
    map->current_size++;
}

static MapKeyElement getKey(KeyValuePair pair)
{
    return pair->key;
}

static void mapSetIteratorInvalid(Map map)
{
    map->iterator=INVALID_ITERATOR;
}
static MapKeyElement getData(KeyValuePair pair)
{
    return pair->value;
}
static void shiftArrayRight(Map map, int index)
{
    if (map == NULL || index >= mapGetSize(map) || index < 0)
    {
        return;
    }
    // check for resize before moving right
    checkResize(map);
    for (int i = mapGetSize(map); i > index; i--)
    {
        map->key_value_pairs[i] = getPair(map,i-1);
    }
}
MapDataElement mapGet(Map map, MapKeyElement keyElement)
{
    //return NULL if not contains
    if (map == NULL || !mapContains(map,keyElement))
    {
        return NULL;
    }
    SearchResults error_code = SEARCH_SUCCESS;
    int index = getSortedIndex(map,keyElement, &error_code );
    if(error_code!=SEARCH_SUCCESS){
        return NULL;
    }
    KeyValuePair pair = getPair(map, index);
    return getData(pair);
}
static void shiftArrayLeft(Map map, int index)
{
    // if index is the last on the list nothing should happened
    if (map == NULL || index >= mapGetSize(map) - 1 || index < 0)
    {
        return;
    }
    for (int i = index; i < mapGetSize(map) - 1; i++)
    {
        map->key_value_pairs[i] = getPair(map, i + 1);
    }

    //    freePair(map, getPair(map, mapGetSize(map)-1));
}
int mapGetSize(Map map){
    if (map == NULL)
    {
        return -1;
    }
    return map->current_size;
}

bool mapContains(Map map, MapKeyElement element)
{
    SearchResults error_code = SEARCH_SUCCESS;
    // no need to save result into var if only want error code
    getSortedIndex(map,element,&error_code);
    if (error_code == SEARCH_SUCCESS)
    {
        return true;
    }
    else{
        return false; // handle situation: if BinarySearch returns SEARCH_FAILED ? this is good, in h file says false
        // for that too
    }
}
static ResizeResult checkResize(Map map)
{
    // changed to use functions
    if (mapGetSize(map) >= mapGetMaxSize(map))
    {
        return resize(map);
    }
    else{
        return NO_NEED_FOR_RESIZE;
    }
}

static ResizeResult resize(Map map)
{
    if (map == NULL)
    {
        return RESIZE_NULL_ARGUMENT;
    }
    // changed to use function
    int new_size = EXPAND_FACTOR* (mapGetMaxSize(map));
    //keeping map->key_value_pairs
    // KeyValuePair is a pointer to a pair so sizeof struct KeyValuePair
    KeyValuePair *new_array = realloc(map->key_value_pairs,new_size * sizeof(struct KeyValuePair));
    //check if new allocation successful
    if (new_array == NULL)
    {
        return RESIZE_OUT_OF_MEMORY;
    }
    else
    {
        map->key_value_pairs = new_array;
        map->max_size = new_size;
        return RESIZE_SUCCESS;
    }
}

MapResult mapClear(Map map)
{
    if (map == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    // changed here to use mapGetSize
    for (int i = 0; i < mapGetSize(map); i++)
    {
        KeyValuePair pair = getPair(map, i);
        // changed here to use free pair function
        freePair(map, pair);
    }
    map->current_size = 0;
    // changed map->max_size = INITIAL_MAP_MAX_SIZE;
    // no reason to resize array and also we are not resizing since the array itself is still full sized
    // we only freed the items in array
    // added to reset iterator as well
    map->iterator = 0;
    return MAP_SUCCESS;
}
void mapDestroy(Map map)
{
    if (map == NULL)
    {
        return;
    }
    mapClear(map); //should i save the output of mapClear? no in h file destroy is void so we have nothing to do with it
    // need to free array in map as well
    free(map->key_value_pairs);
    free(map);

}
