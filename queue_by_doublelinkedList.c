#include <stdio.h>  // scanf/print/ 文件I/O
#include <stdlib.h> // malloc
#include <string.h>  // 操作字符串需要的库函数


// 设计数据结构
struct node
{
    int val;
    struct node* prev;
    struct node* next;
};
typedef struct node Node;

struct queue
{
    Node* head;
    Node* tail;
};
typedef struct queue Queue;

// void queue_print(Queue *q) //TODO 一会儿补写
// {
//     printf("\nqueue content: ");fflush(stdout);
//     Node *cur = q->head->next;
//     while (cur != q->tail)
//     {
//         printf("%d->", cur->val);fflush(stdout);
//         cur = cur->next;
//     }
//     printf("NIL");
//     printf("\n");fflush(stdout);
// }


Queue* queue_create(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = (Node*)malloc(sizeof(Node));
    q->tail = (Node*)malloc(sizeof(Node));
    q->head->next = q->tail;
    q->tail->prev = q->head;
    q->head->prev = NULL;
    q->tail->next = NULL;
    return q;
}


void test_queue(){
    //server as test driver
    printf("This is the test function\n");
    Queue* myq = queue_create();
}

int main(int argc, char* argv[]){
    test_queue();
    // queue_interaction();
    return 0;
}