#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    char value;
    struct _Node * next;
} Node;

/* circular List, its last node points to the head */
typedef struct {
    Node * head;
    Node * tail;
    int length;
} CList;

/* input is address of CList, which has allocated memory */
void clist_init(CList * l)
{
    Node *n = (Node *)malloc(sizeof(Node));
    l->head = n;
    l->head->next = l->head;
    l->tail = l->head;
    l->length = 0;
}

void clist_print(CList *l)
{
    printf("%d: ", l->length);

    Node * n = l->head->next;
    while(n != l->head){
        printf("%c ", n->value);
        n = n->next;
    }
    printf("\n");
}

void clist_append(CList *l, char c)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = c;
    n->next = l->head;
    l->tail->next = n;
    l->tail = n;
    l->length ++;
}

void clist_insert(CList *l, int i, char c)
{
    if(i < 1 || i > l->length + 1)
        return;

    int pos = 1;
    Node *prev = l->head;
    Node *n = l->head->next;
    while(n != l->head){
        if(pos == i)
            break;
        prev = n;
        n = n->next;
        pos ++;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = c;
    new_node->next = n;
    prev->next = new_node;
    if(n == l->head)
        l->tail = new_node;
    l->length ++;
}

void clist_delete(CList *l, int i)
{
    if(i < 1 || i > l->length)
        return;

    int pos = 1;
    Node *prev = l->head;
    Node *n = l->head->next;
    while(n != l->head){
        if(pos == i) break;
        prev = n;
        n = n->next;
        pos ++;
    }

    prev->next = n->next;
    if(l->tail == n)
        l->tail = prev;
    free(n);
    l->length --;
}

void clist_clear(CList *l)
{
    int i;
    for(i = 0; i < l->length; i ++){
        clist_delete(l, 1);
    }
}

int main(int argc, char *argv[])
{
    CList cl;
    clist_init(&cl);
    clist_append(&cl, 'a');
    clist_print(&cl);
    clist_append(&cl, 'c');
    clist_print(&cl);
    clist_append(&cl, 'd');
    clist_print(&cl);

    clist_insert(&cl, 1, 'x');
    clist_print(&cl);
    clist_insert(&cl, 1, 'w');
    clist_print(&cl);
    clist_insert(&cl, 1, 'y');
    clist_print(&cl);
    clist_insert(&cl, 1, 'z');
    clist_print(&cl);

    clist_delete(&cl, 2);
    clist_print(&cl);
    clist_delete(&cl, 2);
    clist_print(&cl);
    clist_delete(&cl, 2);
    clist_print(&cl);
    clist_delete(&cl, 2);
    clist_print(&cl);
    clist_delete(&cl, 2);
    clist_print(&cl);

    clist_clear(&cl);
    clist_print(&cl);
    return 0;
}
