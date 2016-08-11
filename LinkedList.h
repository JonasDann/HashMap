#ifndef HASHMAP_LINKEDLIST_H
#define HASHMAP_LINKEDLIST_H

typedef struct Element {
    void *value;
    struct Element *next;
} Element;

typedef struct LinkedList {
    Element *firstElement;
    Element *lastElement;
    int length;
} LinkedList;

LinkedList *createLinkedList();
LinkedList *duplicateLinkedList(LinkedList *list);
void add(LinkedList *list, void *value);
void append(LinkedList *list, void *value);
void recalcLength(LinkedList *list);
void freeLinkedList(LinkedList *list);

#endif //HASHMAP_LINKEDLIST_H
