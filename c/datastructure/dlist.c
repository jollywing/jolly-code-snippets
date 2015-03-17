#include "stdio.h"
#include "stdlib.h" // for malloc and free

typedef struct _Node{
    struct _Node* prev;
    int value;
    struct _Node* next;
} Node;

typedef struct _DList{
    Node * head;
    Node * tail;
} DList;

void dlist_destroy(DList * list){
    Node * next_node;
    Node * current_node;
    current_node = list->head;

    while (current_node != 0){
        next_node = current_node->next;
        printf("delete %d!\n", current_node->value);
        free(current_node);
        current_node = next_node;
    }

    printf("delete list completely!\n");
    free(list);
    list = 0;
}

DList * dlist_create(int node_num){
    DList* list = malloc(sizeof(DList));
    list->head = malloc(sizeof(Node));
    Node * current_node = list->head;
    Node* prev_node = 0;
    int i;
    for(i =0; i < node_num; ++i){
        current_node->prev = prev_node;
        current_node->value = i;
        if (i == node_num -1)
            current_node->next = 0;
        else{
            printf("create Node %d!\n", i+1);
            current_node->next = malloc(sizeof(Node));
        }
        prev_node = current_node;
        current_node = current_node->next;
    }
    list->tail = prev_node;
    return list;
}

void dlist_go_through(DList * list){
    printf("go through list: ");
    Node * current_node = list->head;
    while (current_node != 0){
        printf("%d ", current_node->value);
        current_node = current_node->next;
    }
    printf("\n");
}

void dlist_through_reversely(DList * list){
    printf("go through list reversely: ");
    Node * current_node = list->tail;
    while (current_node != 0){
        printf("%d ", current_node->value);
        current_node = current_node->prev;
    }
    printf("\n");
}

int main()
{
    DList * list = dlist_create(10);
    dlist_go_through(list);
    dlist_through_reversely(list);
    dlist_destroy(list);
    return 0;
}

