#include <stdlib.h> // define NULL
#include <stdio.h>

typedef struct _Node {
    int value;
    struct _Node *next;
} Node;

void print_list(Node *head)
{
    Node *temp = head;
    while(temp) {
        printf("%d", temp->value);
        if(temp->next) {
            printf("->");
        }
        else {
            printf(".");
        }
        temp = temp->next;
    }
    printf("\n");
}

void loop_reverse(Node **phead)
{
    Node *node, *prev_node, *next_node;
    for(node = *phead, prev_node = NULL; node;){
        next_node = node->next;
        node->next = prev_node;
        prev_node = node;
        node = next_node;
    }
    *phead = prev_node;
}

// return new head
Node * recursive_reverse(Node *node, Node *prev_node)
{
    if(!node){
        return prev_node;
    }

    Node *next_node = node->next;
    node->next = prev_node;
    return recursive_reverse(next_node, node);
}

int main(int argc, char *argv[])
{
    Node n1, n2, n3, n4, n5;
    n1.value = 1;
    n1.next = &n2;
    n2.value = 2;
    n2.next = &n3;
    n3.value = 3;
    n3.next = &n4;
    n4.value = 4;
    n4.next = &n5;
    n5.value = 5;
    n5.next = NULL;

    Node *head = &n1;

    print_list(head);
    loop_reverse(&head);
    print_list(head);

    head = recursive_reverse(head, NULL);
    print_list(head);
    
    return 0;
}
