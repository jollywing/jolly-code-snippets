
#include <stdlib.h> // define NULL
#include <stdio.h>

typedef char bool;
#define false 0
#define true 1

typedef struct _Node {
    int value;
    struct _Node *next;
} Node;

// algorithm: Has any loop in a given list?
// let p1 and p2 point to the head.
// then left p1 forward by one step, p2 forward by 2 step, and so on
// if p1 == p2, then the list has a loop.
// if p2 meets NULL, then the list has no loop.
bool has_loop(Node * head)
{
    Node * p1, * p2;
    p1 = p2 = head;
    while (p2 != NULL && p2 -> next != NULL){
        p1 = p1 -> next;
        printf("p1 -> %d, ", p1->value);
        p2 = p2 -> next -> next;
        if(p2)
            printf("p2 -> %d\n", p2->value);
        else
            printf("p2 -> NULL\n");
        if(p1 == p2)
            return true;
    }
    return false;
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
    if(has_loop(head)){
        printf("The list has loop!\n");
    }
    else
        printf("The list has no loop!\n");

    Node n6;
    n6.value = 6;
    n6.next = &n1;
    n5.next = &n6;
    if(has_loop(head)){
        printf("The new list has loop!\n");
    }
    else
        printf("The new list has no loop!\n");
    return 0;
}
