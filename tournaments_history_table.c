//
// Created by DELL on 11/05/2021.
//

#include "game_history.h"


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

