#include <stdio.h>

typedef struct _Node {
    int value;
    struct _Node *next;
} Node;

Node * get_mid_node(Node *head)
{
  Node *p1, *p2;
  p1 = p2 = head;
  while(p2 && p2->next) {
    p1 = p1 -> next;
    p2 = p2->next->next;
  }
  return p1;
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
    Node *mid;
    mid = get_mid_node(head);
    printf("The mid node is %d\n", mid->value);
    return 0;
}

