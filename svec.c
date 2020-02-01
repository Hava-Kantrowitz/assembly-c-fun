/* This file is lecture notes from CS 3650, Fall 2018 */
/* Author: Nat Tuck */

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "svec.h"

svec*
make_svec()
{
    svec* sv = malloc(sizeof(svec));
    sv->data = malloc(2 * sizeof(char*));
    sv->size = 0;
    sv->capacity = 2;
    return sv;
}

void
free_svec(svec* sv)
{
    for (int i = 0; i < sv->size; i++) {
	    free(sv->data[i]);
    }
    free(sv->data);
    free(sv);
}

char*
svec_get(svec* sv, int ii)
{
    assert(ii >= 0 && ii < sv->size);
    return sv->data[ii];
}

void
svec_put(svec* sv, int ii, char* item)
{
    assert(ii >= 0 && ii < sv->size);
    sv->data[ii] = strdup(item);
}

void
svec_push_back(svec* sv, char* item)
{
    int ii = sv->size;
    int jj = sv->capacity; 


    if (ii >= jj/2) {

      char** new_data = realloc(sv->data, (jj*2) * sizeof(char*)); 
      sv->data = new_data; 
      sv->capacity = jj*2; 
    }

    sv->size = ii + 1;
    //printf("Size is %d\n", sv->size);
    //printf("Capacity is %d\n", sv->capacity);
    svec_put(sv, ii, item);
}

void
svec_swap(svec* sv, int ii, int jj)
{
    char* firstItem = sv->data[ii];
    char* secondItem = sv->data[jj];

    sv->data[ii] = secondItem;
    sv->data[jj] = firstItem; 
}

svec*
create_svec(svec* old_svec, int capacity) {
    svec* sv = malloc(sizeof(svec));
    sv->data = old_svec->data;
    sv->size = old_svec->size;
    sv->capacity = capacity;
    return sv;
}
