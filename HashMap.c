#include "HashMap.h"

typedef struct KeyValuePair {
    void *key;
    void *value;
} KeyValuePair;

HashMap *createHashMap(int (*hashCode)(void *), bool (*equals)(void *, void *)) {
    HashMap *result = malloc(sizeof(HashMap));
    result->hashCode = hashCode;
    result->equals = equals;
    //result->bucketCount = initialBuckets;
    result->bucketCount = 2;
    result->hashBuckets = malloc(sizeof(LinkedList *) * result->bucketCount);
    for (int i = 0; i < result->bucketCount; i++) {
        result->hashBuckets[i] = createLinkedList();
    }
    return result;
}

void freeHashBuckets(HashMap *hashMap) {
    LinkedList *bucket;
    Element *element;
    for (int i = 0; i < hashMap->bucketCount; i++) {
        bucket = hashMap->hashBuckets[i];
        element = bucket->firstElement;
        while (element != 0) {
            free(element->value);
            element = element->next;
        }
        freeLinkedList(bucket);
    }
    free(hashMap->hashBuckets);
}

void rehash(HashMap *hashMap, size_t newBucketCount) {
    LinkedList **newHashBuckets = malloc(sizeof(LinkedList *) * newBucketCount);
    for (int i = 0; i < newBucketCount; i++) {
        newHashBuckets[i] = createLinkedList();
    }
    LinkedList *bucket;
    Element *element;
    KeyValuePair *pair;
    int index;
    for (int i = 0; i < hashMap->bucketCount; i++) {
        bucket = hashMap->hashBuckets[i];
        element = bucket->firstElement;

        while (element != 0) {
            pair = element->value;
            index = hashMap->hashCode(pair->key) % newBucketCount;
            add(newHashBuckets[index], pair);
            element = element->next;
        }
        freeLinkedList(bucket);
    }
    free(hashMap->hashBuckets);
    hashMap->hashBuckets = newHashBuckets;
    hashMap->bucketCount = newBucketCount;
}

void put(HashMap *hashMap, void *key, void *value) {
    int index = hashMap->hashCode(key) % hashMap->bucketCount;
    LinkedList *bucket = hashMap->hashBuckets[index];
    KeyValuePair *pair = malloc(sizeof(KeyValuePair));
    pair->key = key;
    pair->value = value;
    add(bucket, pair);
    //if (bucket->length > rehashLimit) {
    if (bucket->length > 5) {
        rehash(hashMap, hashMap->bucketCount * 2);
    }
}

void *get(HashMap *hashMap, void *key) {
    void *result = 0;
    int index = hashMap->hashCode(key) % hashMap->bucketCount;
    LinkedList *bucket = hashMap->hashBuckets[index];
    Element *element = bucket->firstElement;
    KeyValuePair *pair;
    while (element != 0) {
        pair = element->value;
        if (hashMap->equals(pair->key, key)) {
            result = pair->value;
            break;
        }
        element = element->next;
    }
    return result;
}

void remove(HashMap *hashMap, void *key) {
    int index = hashMap->hashCode(key) % hashMap->bucketCount;
    LinkedList *bucket = hashMap->hashBuckets[index];
    Element *prevElement = bucket->firstElement;
    Element *element = bucket->firstElement;
    if (element != 0) {
        KeyValuePair *pair = element->value;
        if (hashMap->equals(pair->key, key)) {
            bucket->firstElement = element->next;
            bucket->length--;
            free(pair);
            free(element);
        } else {
            element = element->next;
            while (element != 0) {
                pair = element->value;
                if (hashMap->equals(pair->key, key)) {
                    prevElement->next = element->next;
                    if (element->next == 0) {
                        bucket->lastElement = prevElement;
                    }
                    bucket->length--;
                    free(pair);
                    free(element);
                    break;
                }
                prevElement = element;
                element = element->next;
            }
        }
    }
}

void freeHashMap(HashMap *hashMap) {
    freeHashBuckets(hashMap);
    free(hashMap);
}