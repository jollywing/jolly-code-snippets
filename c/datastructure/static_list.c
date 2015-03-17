
#include <stdio.h>
#define MAX_SIZE 255

#define OK 0
#define ERROR_OVERFLOW 1

typedef struct {
    unsigned char v;
    int next;
} ListNode, StaticList[MAX_SIZE];

/* StaticList is address */
/* TIME: O(n) */
void list_init(StaticList l)
{
    int i;

    l[0].v = 0;
    l[0].next = 0;

    for(i = 1; i < MAX_SIZE; i ++)
        l[i].next = -1;
}

/* O(n) */
int list_append(StaticList l, char c)
{
    int i, new_pos;
    for(i = 0; i < MAX_SIZE; i ++){
        if(l[i].next == -1){
            new_pos = i;
            break;
        }
    }
    if(i == MAX_SIZE) {
        return ERROR_OVERFLOW;
    }

    int last = l[0].v;
    l[last].next = new_pos;

    l[0].v = new_pos;
    l[new_pos].v = c;
    l[new_pos].next = 0;
    return OK;
    
}

/* O(n) */
int list_size(StaticList l)
{
    int cur = l[0].next;
    int count = 0;
    while(cur > 0){
        cur = l[cur].next;
        count ++;
    }
    return count;
}

int list_insert(StaticList l, int position, char c)
{
    int i, new_el_pos;
    for(i = 0; i < MAX_SIZE; i++){
        if(l[i].next == -1){
            new_el_pos = i;
            break;
        }
    }
    if(i == MAX_SIZE)
        return ERROR_OVERFLOW;

    l[new_el_pos].v = c;

    int id = 0;
    int cur = l[0].next;
    while(cur > 0){
        id ++;
        if(id >= position)
            break;
        cur = l[cur].next;
    }
    if(cur == 0)
        return ERROR_OVERFLOW;

    l[new_el_pos].next = l[cur].next;
    l[cur].next = new_el_pos;
    return 0;
}

/* O(n) */
int list_delete(StaticList l, char c)
{
    int cur, prev;
    prev = 0;
    cur = l[0].next;
    while(cur > 0){
        if(l[cur].v == c){
            l[prev].next = l[cur].next;
            l[cur].next = -1;
            cur = l[prev].next;
        }
        else {
            prev = cur;
            cur = l[cur].next;
        }
    }

    return 0;
}

void list_clear(StaticList l)
{
    int cur, id;
    cur = l[0].next;
    while(cur > 0){
        id = cur;
        cur = l[cur].next;
        l[id].next = -1;
    }
    l[0].v = 0;
    l[0].next = 0;
}

/* O(n) */
void list_print(StaticList l)
{
    printf("%d: ", list_size(l));

    int cur = l[0].next;
    while(cur > 0){
        printf("%c ", l[cur].v);
        cur = l[cur].next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    StaticList l;

    /* test append */
    list_init(l);
    list_append(l, 'c');
    list_append(l, 'd');
    list_append(l, 'c');
    list_print(l);

    /* test delete */
    list_delete(l, 'c');
    list_print(l);

    /* test insert */
    list_insert(l, 1, 'x');
    list_print(l);
    list_insert(l, 1, 'y');
    list_print(l);
    list_insert(l, 1, 'z');
    list_print(l);

    /* test clear */
    list_clear(l);
    list_print(l);
    return 0;
}
