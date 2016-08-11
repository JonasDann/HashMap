#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"

//size_t initialBuckets = 2;
//size_t rehashLimit = 5;

typedef struct HashMap {
    int (*hashCode)(void *);
    bool (*equals)(void *, void *);
    LinkedList **hashBuckets;
    size_t bucketCount;
} HashMap;

HashMap *createHashMap(int (*hashCode)(void *), bool (*equals)(void *, void *));
void put(HashMap *hashMap, void *key, void *value);
void *get(HashMap *hashMap, void *key);
void remove(HashMap *hashMap, void *key);
void freeHashMap(HashMap *hashMap);

#endif //HASHMAP_HASHMAP_H
