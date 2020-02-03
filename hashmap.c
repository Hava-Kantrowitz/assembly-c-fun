
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
    //Note: This hash is heavily based in the hash Professor Tuck created in class
    int hash = 0;
    for (int i = 0; i < key[i]; i++) {
	    hash = hash * 127 + key[i];
    }
    return hash;
}

hashmap*
make_hashmap_presize(int nn)
{
    hashmap* hh = calloc(1, sizeof(hashmap));
    hh->data = malloc(nn * sizeof(hashmap_pair*));

    for (int i = 0; i < nn; i++) {
	hh->data[i] = malloc(sizeof(hashmap_pair));
	hh->data[i]->key = calloc(4, sizeof(char));
	hh->data[i]->val = 0;
	hh->data[i]->used = false;
	hh->data[i]->tomb = false; 
    }
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
   
   for (int i = 0; i < hh->capacity; i++) {
	   free(hh->data[i]->key);
   }
   free(hh->data);  
   free(hh);
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
    // if it's the right hash, look and try to match keys
    // Once a key is matched, return the data
    // Once keys are run out, if match isn't found, return -1 
   int hashVal = hash(kk);
   int hashNum = hashVal % hh->capacity;
   for (int j = hashNum; j < hh->capacity; j++) {
        if (hh->data[j]->used) {
		if (strcmp(hh->data[j]->key, kk)) {
			return hh->data[j]->val;
		} 
        }
	return -1; 
    }

    return -1; 
}

void
hashmap_put(hashmap* hh, char* kk, int vv)
{
    // Insert the value 'vv' into the hashmap
    // for the key 'kk', replacing any existing value
    // for that key.
    int cap = hh->capacity;
    printf("Before size is %d, before capacity is %d\n", hh->size, hh->capacity);
    if (hh->size >= cap/2) {
	hh->capacity = hh->capacity * 2;
	hashmap_pair** old_hash = calloc(1, hh->capacity * sizeof(hashmap_pair*)); 
	for (int i = 0; i < hh->size; i++) { 
		old_hash[i] = calloc(1, sizeof(hashmap_pair));
		old_hash[i]->key = calloc(1, sizeof(char*));
		strcpy(old_hash[i]->key, hh->data[i]->key);
		old_hash[i]->val = hh->data[i]->val;
		old_hash[i]->used = hh->data[i]->used;
		old_hash[i]->tomb = hh->data[i]->used; 
	}
	printf("After size is %d, after capacity is %d\n", hh->size, hh->capacity);
	hh->data  = realloc(hh->data, (hh->capacity) * sizeof(hashmap_pair*));
	for (int i = 0; i < cap; i++) {
		hh->data[i] = calloc(1, sizeof(hashmap_pair)); 
		hh->data[i]->used = false;
		hh->data[i]->tomb = false;
	}
	for (int i = 0; i < hh->capacity; i++) {
	    if (old_hash[i]->used && !old_hash[i]->tomb) {
		hashmap_put(hh, old_hash[i]->key, old_hash[i]->val);
	    }	
	    free(old_hash[i]);
	}

	free(old_hash); 

	
    }

    hh->size += 1; 
    int hashVal = hash(kk); 
    int hashNum = hashVal % hh->capacity;

    for (int j = hashNum; j <= hh->capacity; j++) {
	if (j == hh->capacity) { 
		j = 0;
	}
        if (!hh->data[j]->used) {
           hh->data[j]->val = vv;
           strcpy(hh->data[j]->key, kk);
           hh->data[j]->used = true; 
	   j = hh->capacity + 10; 
        }
    }

    printf("NEW LOOP\n");

	//for each element in the hash table starting from the hashVal, keep looking until empty slot is found, place in that slot 	
    
    
}

void
hashmap_del(hashmap* hh, char* kk)
{
    int hashVal = hash(kk);
    int hashNum = hashVal % hh->capacity;
    if (hashmap_has(hh, kk)) {
      for (int j = hashNum; j < hh->capacity; j++) {
        if (hh->data[j]->used) {
		if (strcmp(hh->data[j]->key, kk)) {
			free(hh->data[j]->key);
			hh->data[j]->val = 0;
			hh->data[j]->used = false;
			hh->data[j]->tomb = true;
		} 
        }
	else {
		j = hh->capacity + 10;
	}	
    }

    }
    
}

hashmap_pair
hashmap_get_pair(hashmap* hh, int ii)
{
    // Get the {k,v} pair stored in index 'ii'.
    return *hh->data[ii];
}

void
hashmap_dump(hashmap* hh)
{
    printf("== hashmap dump ==\n");
    for (int i = 0; i < hh->size; i++) {
	    hashmap_pair pair = hashmap_get_pair(hh, i);
	    if (pair.used) {
	    char* key = pair.key;
	    int val = pair.val; 
	    printf("Key: %s, Val: %d\n", key, val); 
	    }
    }
    printf("Size is %d, Capacity is %d\n", hh->size, hh->capacity);
}
