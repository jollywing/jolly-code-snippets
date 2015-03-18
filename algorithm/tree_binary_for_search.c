
/* @purpose: 定义二叉查找树，左子节点比父节点小，右子节点比父节点大
 * @author: jollywing@foxmail.com
 * @date: 2015-03-18 Wed
 * */
#include <assert.h>
#include <stdlib.h>

typedef struct __BinaryTreeNode BinaryTreeNode;

struct __BinaryTreeNode {
    int key;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
};

BinaryTreeNode *new_tree_node(int value)
{
    BinaryTreeNode * node = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    if(!node) return 0;

    node->key = value;
    node->left = 0;
    node->right = 0;
}

BinaryTreeNode * add_tree_node(BinaryTreeNode *tree, int value)
{
    if(value < tree->key){
        if (!tree->left) {
            BinaryTreeNode *node = new_tree_node(value);
            tree->left = node;
            return node;
        }
        else {
            return add_tree_node(tree->left, value);
        }
    }
    else if(value > tree->key){
        if (!tree->right) {
            BinaryTreeNode *node = new_tree_node(value);
            tree->right = node;
            return node;
        }
        else
            return add_tree_node(tree->right, value);
    }
    return 0;
}

/* 中序遍历 */
int main(int argc, char *argv[])
{
    /* Test new tree node */
    BinaryTreeNode *treeroot = new_tree_node(5);
    assert(treeroot);
    assert(treeroot->key == 5);

    add_tree_node(treeroot, 15);
    return 0;
}
