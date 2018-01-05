#ifndef HASHTABLE_H
#define HASHTABLE_H
/*
 * Stolen and adapted from https://gist.github.com/tonious/1377667
 */

typedef struct hashtable_s hashtable_t;
typedef struct entry_s entry_t;

hashtable_t* ht_create(int);
void ht_set(hashtable_t*, char*, void*);
void* ht_get(hashtable_t*, char*);

struct entry_s {
    char* key;
    void* value;
    entry_t* next;
};

struct hashtable_s {
    int size;
    entry_t** table;
};

#endif