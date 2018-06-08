#ifndef TS_QUEUE_H
#define TS_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Design data struct
typedef struct node
{
    int val;
    struct node *prev;
    struct node *next;
} Node;

typedef struct queue
{
    Node* head;
    Node* tail;
} Queue;


void queue_print(Queue *q);
void print_recursion_helper(Queue *q, Node *cur);
void queue_print_recursion(Queue *q);
Queue *queue_create();
void queue_append(Queue *q, int val);
int queue_pop(Queue *q);
void queue_delete(Queue *q, int target);
int queue_insert_somewhere(Queue *q, int val, int app_val);
void readfile(Queue *q, char *filename);
void test_queue();
void queue_interaction();


#endif