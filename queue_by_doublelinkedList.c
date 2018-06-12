#include <stdio.h>  // scanf/print/ 文件I/O
#include <stdlib.h> // malloc
#include <string.h>  // 操作字符串需要的库函数

//用来测试的Macro
#define require(p)                                                                                     \
    do                                                                                                 \
    {                                                                                                  \
        if (!(p))                                                                                      \
        {                                                                                              \
            fprintf(stderr, "\"%s\" failed in %s:%d (%s)\n", #p, __FILE__, __LINE__, strerror(1)); \
            exit(EXIT_FAILURE);                                                                        \
        }                                                                                              \
    } while (0)


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

void queue_print(Queue *q)
{
    printf("\nqueue content: ");fflush(stdout);
    Node* cur = q->head->next;
    while(cur != q->tail)
    {
        printf("%d <=> ", cur->val);
        cur = cur->next;
    }

    printf("NULL");
    printf("\n");fflush(stdout);
}

Queue *create_queue()
{
    //malloc a queue, and malloc its head and tail
    Queue *q = malloc(sizeof(Queue));
    q->head = malloc(sizeof(Node));
    q->tail = malloc(sizeof(Node));
    q->head->prev = NULL;
    q->tail->next = NULL;
    q->head->next = q->tail;
    q->tail->prev = q->head;
    return q;
}

void push_to_queue(Queue* q, int val)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->val = val;
    new_node->prev = q->tail->prev;
    new_node->next = q->tail;
    Node* op = q->tail->prev;
    op->next = new_node;
    q->tail->prev = new_node;

}

int pop_from_queue(Queue* q)
{
    Node* onext = q->head->next->next;
    Node* cur = q->head->next;
    q->head->next = onext;
    onext->prev = q->head;
    int ret = cur->val;
    free(cur);
    return ret;
}

void delete_node_from_queue(Queue* q, int target_val)
{
    Node* cur = q->head->next;
    while (cur != q->tail && cur->val != target_val)
        cur = cur->next;

    if(cur != q->tail)
    {
        //start delete work

        // cur->next->prev = cur->prev;
        // cur->prev->next = cur->next;

        Node* onext = cur->next;
        Node* oprev = cur->prev;
        onext->prev = oprev;
        oprev->next = onext;
        free(cur);
    }
}

void destruct_queue(Queue* q)
{
    Node* cur = q->head;
    while(cur != NULL)
    {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(q);
}

void test_queue(){
    //server as test driver
    printf("This is the test function >>> \n\n");
    Queue* q = create_queue();
    require(q->head->next == q->tail);
    require(q->tail->prev == q->head);
    push_to_queue(q, 1);
    push_to_queue(q, 2);
    push_to_queue(q, 98);
    push_to_queue(q, 3);
    push_to_queue(q, 666);
    queue_print(q);
    int val = pop_from_queue(q);
    require(val == 1);
    require(q->head->next->val == 2);
    printf("\n%d poped\n", val);
    queue_print(q);
    require(q->tail->prev->val == 666);
    delete_node_from_queue(q, 666);
    require(q->tail->prev->val != 666);
    printf("deleted 666, after deletedd:\n");
    queue_print(q);
    delete_node_from_queue(q, 777);
    printf("deleted 777, after deletedd:\n");
    queue_print(q);

    destruct_queue(q);
}

int main(int argc, char* argv[]){
    test_queue();
    // queue_interaction();
    return 0;
}