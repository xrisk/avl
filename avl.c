#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"

void traverse(Node *root) {
  if (root != NULL) {
    traverse(root->left);
    printf("%d ", root->data);
    traverse(root->right);
  }
}

Node *mknode(int data) {
  Node *n = malloc(sizeof(Node));
  n->data = data;
  n->left = NULL, n->right = NULL, n->parent = NULL;
  return n;
}

AVLTree *mktree() {
  AVLTree *t = malloc(sizeof(AVLTree));
  t->root = NULL;
  return t;
}

Node *find(Node *root, int key) {
  Node *cur = root;
  while (cur != NULL) {
    if (cur->data == key)
      break;
    else if (key < cur->data)
      cur = cur->left;
    else
      cur = cur->right;
  }
  return cur;
}

Node *tree_min(Node *root) {
  if (root == NULL)
    return root;
  while (root->left)
    root = root->left;
  return root;
}

Node *tree_max(Node *root) {
  if (root == NULL)
    return root;
  while (root->right)
    root = root->right;
  return root;
}

Node *successor(Node *x) {
  if (x->right) {
    return tree_min(x->right);
  }
  Node *y = x->parent;
  while (y != NULL && x == y->right) {
    x = y;
    y = x->parent;
  }
  return y;
}

Node *predecessor(Node *x) {
  if (x->left) {
    return tree_max(x->left);
  }
  Node *y = x->parent;
  while (y != NULL && x == y->left) {
    x = y;
    y = x->parent;
  }
  return y;
}

Node *insert(AVLTree *t, Node *z) {
  Node *y = NULL;
  Node *x = t->root;
  while (x != NULL) {
    y = x;
    if (z->data < x->data)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == NULL)
    t->root = z;
  else if (z->data < y->data)
    y->left = z;
  else
    y->right = z;
  return z;
}

void free_node(Node *x) {
  if (x == NULL)
    return;
  free_node(x->left);
  free_node(x->right);
  free(x);
}

void free_tree(AVLTree *x) {
  if (x == NULL)
    return;
  free_node(x->root);
  free(x);
}

/* -------- deletetion routines --------- */

void transplant(AVLTree *t, Node *u, Node *v) {
  if (u->parent == NULL)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;
  if (v != NULL)
    v->parent = u->parent;
}

void delete_node(AVLTree *t, Node *z) {
  if (z->left == NULL)
    transplant(t, z, z->right);
  else if (z->right == NULL)
    transplant(t, z, z->left);
  else {
    Node *y = tree_min(z->right);
    if (y->parent != z) {
      transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
  }
  free_node(z);
}

void test() {
  AVLTree *my = mktree();

  int vals[] = {7, 11, 3, 9, 17, 12, 6, 1, 7, 16};

  for (int i = 0; i < 10; i++) {
    insert(my, mknode(vals[i]));
  }

  assert(tree_min(my->root)->data == 1);
  delete_node(my, find(my->root, 1));

  assert(tree_min(my->root)->data == 3);
  assert(successor(find(my->root, 9))->data = 11);

  traverse(my->root);

  free_tree(my);
}

int main() {
  srand(time(NULL));

  test();
}

// vim: shiftwidth=2:softtabstop=2:expandtab
