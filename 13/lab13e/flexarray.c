#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec{
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s){
    void *result = malloc(s);

    if (result == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

void *erealloc(int *p, size_t s){
    void *result = realloc(p, s);

    if(result == NULL){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

flexarray flexarray_new(){
    flexarray f = emalloc(sizeof *f);
    f->capacity = 2;
    f->itemcount = 0;
    f->items = emalloc(f->capacity * sizeof f->items[0]);

    return f;
}

void flexarray_append(flexarray f, int num){
    if(f->capacity == f->itemcount){
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount] = num;
    f->itemcount++;
}

void flexarray_print(flexarray f){
    int i;

    for(i = 0; i < f->itemcount; i++){
        fprintf("%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f){
    int i, j, smallVal, temp;
    int smallInd = 0;

    for (i = 0; i < f->itemcount; i++){
        smallVal = f->items[i];
        smallVal = i;

        if (i == f->itemcount/2){
            flexarray_print(f);
        }

        for(j = i; j < f->itemcount; j++){
            if(f->items[j] < smallVal){
                smallVal = f->items[j];
                smallInd = j;
            }
        }
        temp = f->items[i];
        f->items[i] = smallVal;
        f->items[smallInd] = temp;
    }
}

void flexarray_free(flexarray f){
    free(f->items);
    free(f);
}
