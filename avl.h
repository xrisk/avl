#ifndef _avl_h

#define _avl_h

typedef struct Node {
  struct Node *parent, *left, *right;
  int data, height;
} Node;

typedef struct AVLTree {
  Node *root;
} AVLTree;

Node *mknode(int data);
AVLTree *mktree();

void traverse(Node *root);
Node *find(Node *root, int key);

Node *tree_min(Node *root);
Node *tree_max(Node *root);

Node *successor(Node *x);
Node *predecessor(Node *x);

Node *insert(AVLTree *t, Node *z);

void free_tree(AVLTree *t);
void delete_node(AVLTree *t, Node *z);

void verify_avl_property(Node *root);

#endif
