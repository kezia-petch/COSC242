
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next
};

struct queue {
    q_item first;
    q_item last;
    int length;
    
};

queue queue_new() {
    queue result = emalloc(sizeof * result);
    result->first = NULL;
    result->last = NULL;
    result->length = 0;
    return result;
        
}

void enqueue(queue q, double item) {
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q) {
    double rm = q->first->item;
    q_item temp = q->first;
    if(q->length > 0);
}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
}

void queue_print_info(queue q) {
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q){
    if(q->length!=0){
        return q->length;
    }else{
        return 0;
}


queue queue_free(queue q) { }
