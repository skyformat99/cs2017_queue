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

void queue_print(Queue *q)
{
    Node* cur = q->head->next;
    while(cur != q->tail)
    // while(cur != NULL)
    {
        printf("%d <-> ", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}

void print_recursion_helper(Queue* q, Node* cur)
{
    if (cur == q->tail)
    {
        printf("NULL\n");
        return;
    }
    else
        printf("%d <=> ", cur->val);
        print_recursion_helper(q, cur->next);
}

void queue_print_recursion(Queue* q)
{
    print_recursion_helper(q, q->head->next);
}


Queue* queue_create(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = (Node*)malloc(sizeof(Node));
    q->tail = (Node*)malloc(sizeof(Node));
    q->head->val = 2147483648-1;
    q->tail->val = 2147483648-1;
    q->head->next = q->tail;
    q->tail->prev = q->head;
    q->head->prev = NULL;
    q->tail->next = NULL;
    return q;
}

void queue_append(Queue* q, int val){
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->val = val;
    Node* original_prev = q->tail->prev;
    q->tail->prev = new_node;
    original_prev->next= new_node;
    new_node->next = q->tail;
    new_node->prev = original_prev;
}

int queue_pop(Queue* q)
{
    Node* ret = q->head->next;
    int ret_val = ret->val;
    Node* new_head_next = ret->next;
    q->head->next = new_head_next;
    new_head_next->prev = q->head;
    // ret->next = NULL;
    // ret->prev = NULL;
    free(ret);
    return ret_val;
}


void queue_delete(Queue* q, int target)
{
    //1. find target node
    Node* cur = q->head->next;
    while(cur != q->tail && cur->val != target){
        cur = cur->next;
    }
    //2. delete target node
    //  2.1 get orignal prev, and next
    //  2.2 connect o'prev, o'next
    //  2.3 free target node
    if(cur != q->tail){
        Node* oprev = cur->prev;
        Node* onext = cur->next;
        oprev->next = onext;
        onext->prev = oprev;
        free(cur);
    }
}

int queue_insert_somewhere(Queue *q, int val, int app_val)
{
    int success = 1;
    Node *cur;
    cur = q->head->next;
    while (cur != q->tail && cur->val != val)
    {
        cur = cur->next;
    }
    if (cur == q->tail)
    {
        success = 0;
    }
    else
    {
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->val = app_val;

        Node* original_next = cur->next;
        new_node->next = original_next;
        new_node->prev = cur;
        cur->next = new_node;
        original_next->prev = new_node;
    }

    return success;
}

void readfile(Queue* q, char* filename)
// read number from file and append them to the queue
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("file open on %s error!\n", filename);
    }
    else
    {
        int elem;
        while(!feof(fp))
        {
            fscanf(fp, "%d", &elem);
            queue_append(q, elem);
        }
    }
    fclose(fp);
}

void test_queue(){
    //server as test driver
    printf("This is the test function\n");
    Queue* myq = queue_create();
    // myq.append(1);
    queue_append(myq, 1);
    queue_append(myq, 2);
    queue_append(myq, 3);
    queue_append(myq, 4);
    // printf("the original queue is:\n");
    queue_print(myq);
    queue_print_recursion(myq);
    // int popval = queue_pop(myq);
    // printf("pop'ed a val from myq, it is : %d\n", popval);
    // queue_print(myq);
    // printf("insert 666 after 3\n");
    // queue_insert_somewhere(myq, 3, 666);
    // queue_print(myq);
    // printf("readfile file1.txt\n");
    // readfile(myq, "./file1.txt");
    // queue_print(myq);
}

void queue_interaction()
{
    char command[100];
    Queue* queue = queue_create();
    while(scanf("%s", command))
    {
        if(strcmp(command, "pop") == 0){
            int res = queue_pop(queue);
            printf("pop'ed %d\n", res);
        }
        else if(strcmp(command, "print") == 0){
            queue_print(queue);
        }
        else if(strcmp(command, "append") == 0){
            int elem;
            scanf("%d", &elem);
            queue_append(queue, elem);
            printf("append'ed %d\n", elem);
        }        
        else if(strcmp(command, "delete") == 0){
            int elem;
            scanf("%d", &elem);
            queue_delete(queue, elem);
            printf("delete'ed %d\n", elem);
        }        
        else if(strcmp(command, "readfile") == 0){
            char fn[100];
            FILE *fp;
            scanf("%s", fn);
            fp = fopen(fn, "r");
            if(!fp){
                printf("No such file\n");
            }
            else{
                printf("Gonna do file read %s\n", fn);
                readfile(queue, fn);
            }
        }        
        else
        {
            printf("Unknow command %s\n", command);fflush(stdout);
            strcpy(command, "");
        }
    }
}

int main(int argc, char* argv[])
{
    test_queue();
    // queue_interaction();
    return 0;
}
