
#include <stdio.h>
#include <stdlib.h>

struct _TreeNode 
{
    struct _TreeNode *parent;
    int nodeValue;
    char visited;
    struct _TreeNode *children;
    struct _TreeNode *left, *right;
};

typedef struct _TreeNode TreeNode;

TreeNode * tree_node_new(int value)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if(!node) {
        printf("TREE_NODE_NEW: allocating memory failed!\n");
        return NULL;
    }
    
    node->nodeValue = value;
    node->visited = 0;
    node->left = node->right = NULL;
    node->parent = node->children = NULL;
    return node;
}

void tree_node_delete(TreeNode *node)
{
    if(node){
        printf("delete node with value %d.\n", node->nodeValue);
        if (node->parent && node->parent->children == node)
            node->parent->children = node->right;
        if (node->left){
            node->left->right = node->right;
        }
        if(node->right)
            node->right->left = node->left;
        free(node);
        node = NULL;
    }
}

void tree_node_go_through(TreeNode *node)
{
    printf("node %d accessed.\n", node->nodeValue);
    node->visited = 1;
}

TreeNode * tree_node_unvisited_child(TreeNode *node)
{
    TreeNode *child = node->children;
    if(!node || !child) return NULL;
    while(child){
        if(!child->visited)
            return child;
        child = child->right;
    }
    return NULL;
}

// In C, function names can not be same.
void tree_append_node(TreeNode *parent, TreeNode *new_node)
{
    new_node->parent = parent;

    if(parent->children == NULL){
        parent->children = new_node;
        new_node->left = new_node->right = NULL;
    }
    
    else {
        TreeNode *temp = parent->children;
        while(temp->right){
            temp = temp->right;
        }
        temp->right = new_node;
        new_node->left = temp;
        new_node->right = NULL;
    }

}

TreeNode * tree_append_value(TreeNode *parent, int insert_value)
{
    TreeNode *node = tree_node_new(insert_value);
    tree_append_node(parent, node);
    return node;
}

// 深度优先, 递归遍历
void tree_dfs_r_go_through(TreeNode *root)
{
    TreeNode *node = root;
    while(node){
        printf("%d ", node->nodeValue);
        tree_dfs_r_go_through(node->children);
        node = node->right;
    }
}

void tree_dfs_r_destroy(TreeNode *root)
{
    TreeNode *node = root;
    while(node){
        tree_dfs_r_destroy(node->children);
        tree_node_delete(node);
        node = node->right;
    }
}

// error: variably modified ‘nodes’ at file scope
// const int STACK_SIZE = 1024;
#define STACK_SIZE 1024

typedef struct _NodeStack 
{
    TreeNode *nodes[STACK_SIZE];
    int ptr;
} NodeStack;

void node_stack_clear(NodeStack *stack)
{
    stack->ptr = -1;
}

char node_stack_is_clear(NodeStack *stack)
{
    if(stack->ptr == -1)
        return 1;
    else
        return 0;
}

TreeNode * node_stack_get_node(NodeStack *stack)
{
    return stack->nodes[stack->ptr];
}

TreeNode * node_stack_push(NodeStack *stack, TreeNode *node)
{
    if(stack->ptr == STACK_SIZE - 1){
        printf("stack full!\n");
        return NULL;
    }
    stack->ptr ++;
    stack->nodes[stack->ptr] = node;
    tree_node_go_through(node);
}

TreeNode * node_stack_popup(NodeStack *stack)
{
    if(node_stack_is_clear(stack)){
        printf("Stack empty!\n");
        return NULL;
    }
    stack->ptr --;
    return stack->nodes[stack->ptr + 1];
}

void tree_dfs_stack_go_through(TreeNode *node)
{
    NodeStack stack;
    node_stack_clear(&stack);

    if(!node) return;
    else {
        node_stack_push(&stack, node);
    }

    TreeNode *temp, *child;
    
    while(!node_stack_is_clear(&stack)){
        temp = node_stack_get_node(&stack);
        if (child = tree_node_unvisited_child(temp)) {
            node_stack_push(&stack, child);
        }
        else if(temp->right) {
            node_stack_popup(&stack);
            node_stack_push(&stack, temp->right);
        }
        else {
            node_stack_popup(&stack);
        }
    }
    
}

typedef struct _ListNode{
    TreeNode *node;
    struct _ListNode *next;
} ListNode;

ListNode * list_node_create(TreeNode *node)
{
    ListNode *list_node = (ListNode *)malloc(sizeof(ListNode));
    if (!list_node){
        printf("LIST_NODE_CREATE: memory allocation failed!\n");
        return NULL;
    }
    list_node->node = node;
    list_node->next = NULL;
    return list_node;
}

void node_list_destroy(ListNode **head)
{
    ListNode *list_node = *head;
    ListNode *temp;
    
    while(list_node){
        temp = list_node;
        list_node = list_node->next;
        free(temp);
    }
    *head = NULL;
}

void node_list_append(ListNode **head, ListNode *new_node)
{
    if(!(*head)){
        *head = new_node;
        return;
    }

    ListNode *list_node = *head;
    while(list_node->next){
        list_node = list_node->next;
    }
    list_node->next = new_node;
}

ListNode * node_list_append_tree_node(ListNode **head,
                                      TreeNode *tree_node)
{
    ListNode *new_node = list_node_create(tree_node);
    node_list_append(head, new_node);
    return new_node;
}

void node_list_go_through(ListNode *head)
{
    while(head){
        tree_node_go_through(head->node);
        head = head->next;
    }
}


void tree_bfs_go_through(TreeNode *root)
{
    ListNode *cur_lvl_nodes = NULL;
    ListNode *next_lvl_nodes = NULL;
    node_list_append_tree_node(&cur_lvl_nodes, root);

    while(cur_lvl_nodes){
        node_list_go_through(cur_lvl_nodes);

        // node_list_destroy(&next_lvl_nodes);
        next_lvl_nodes = NULL;
        ListNode *list_node = cur_lvl_nodes;
        while(list_node){
            TreeNode *tree_node = list_node->node->children;
            while(tree_node){
                node_list_append_tree_node(&next_lvl_nodes, tree_node);
                tree_node = tree_node->right;
            }
            list_node = list_node->next;
        }

        node_list_destroy(&cur_lvl_nodes);
        cur_lvl_nodes = next_lvl_nodes;
    }
    
}

int main(int argc, char *argv[])
{
    TreeNode *root = tree_node_new(0);
    TreeNode *node1 = tree_append_value(root, 1);
    TreeNode *node2 = tree_append_value(root, 2);
    TreeNode *node3 = tree_append_value(node1, 3);
    TreeNode *node4 = tree_append_value(node1, 4);
    TreeNode *node5 = tree_append_value(node2, 5);
    TreeNode *node6 = tree_append_value(node2, 6);
    TreeNode *node7 = tree_append_value(node6, 7);

    printf("DFS go through with recursive method:\n");
    tree_dfs_r_go_through(root);
    printf("\n----------------------------------\n");

    printf("DFS go through with stack:\n");
    tree_dfs_stack_go_through(root);
    printf("----------------------------------\n");

    printf("BFS go through with linked list:\n");
    tree_bfs_go_through(root);
    printf("----------------------------------\n");
    
    printf("delete the tree with dfs recursive method ...\n");
    tree_dfs_r_destroy(root);
    return 0;
}
