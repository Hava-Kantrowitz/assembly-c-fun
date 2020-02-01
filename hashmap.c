
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// This provides strlcpy
// See "man strlcpy"
#include <bsd/string.h>
#include <string.h>

#include "hashmap.h"


int
hash(char* key)
{
    int hash = 127 * key;
    return hash;
}

hashmap*
make_hashmap_presize(int nn)
{
    hashmap* hh = calloc(1, sizeof(hashmap));
    hashmap_pair* items = calloc(nn, sizeof(hasmap_pair*));
    hh->items = items;
    hh->size = 0;
    hh->capacity = nn;
    return hh;
}

hashmap*
make_hashmap()
{
    return make_hashmap_presize(4);
}

void
free_hashmap(hashmap* hh)
{
    // TODO: Free all allocated data.
}

int
hashmap_has(hashmap* hh, char* kk)
{
    return hashmap_get(hh, kk) != -1;
}

int
hashmap_get(hashmap* hh, char* kk)
{
    // TODO: Return the value associated with the
    // key kk.
    // Note: return -1 for key not found.
}

void
hashmap_put(hashmap* hh, char* kk, int vv)
{
    // TODO: Insert the value 'vv' into the hashmap
    // for the key 'kk', replacing any existing value
    // for that key.
}

void
hashmap_del(hashmap* hh, char* kk)
{
    // TODO: Remove any value associated with
    // this key in the map.
}

hashmap_pair
hashmap_get_pair(hashmap* hh, int ii)
{
    // TODO: Get the {k,v} pair stored in index 'ii'.
}

void
hashmap_dump(hashmap* hh)
{
    printf("== hashmap dump ==\n");
    for (int i = 0; i < hh->size; i++) {
	    hashmap_pair pair = hashmap_get_pair(hh, i);
	    char* key = pair->key;
	    int val = pair->value; 
	    printf("Key: %s, Val: %d\n", key, val); 
    }
}
