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
  if (root == NULL) return root;
  while (root->left) root = root->left;
  return root;
}

Node *tree_max(Node *root) {
  if (root == NULL) return root;
  while (root->right) root = root->right;
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

void rmnode(Node *x) {
  if (x == NULL) return;
  rmnode(x->left);
  rmnode(x->right);
  free(x);
}

void rmtree(AVLTree *x) {
  if (x == NULL) return;
  rmnode(x->root);
  free(x);
}

void test() {
  AVLTree *my = mktree();

  for (int i = 0; i < 10; i++) {
    insert(my, mknode(1 + rand() % 100));
  }

  traverse(my->root);
  free(my);
}

int main() {
  srand(time(NULL));

  test();
}

// vim: shiftwidth=2:softtabstop=2:expandtab
