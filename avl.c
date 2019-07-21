#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"

/* ------ internal functions ------- */

int max(const int a, const int b) { return (a > b) ? a : b; }

void printnode(Node *root) {
  printf("(%d H:%d L:%d R:%d P:%d) ", root->data, root->height,
         (root->left != NULL) ? root->left->data : -1,
         (root->right != NULL) ? root->right->data : -1,
         (root->parent != NULL) ? root->parent->data : -1);
}

int height(Node *x) {
  if (x == NULL)
    return -1;
  else
    return x->height;
}

void update_height(Node *x) {
  x->height = max(height(x->left), height(x->right)) + 1;
}

void left_rotate(AVLTree *t, Node *x);
void right_rotate(AVLTree *t, Node *x);

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

void rebalance(AVLTree *t, Node *x) {
  while (x != NULL) {
    update_height(x);
    if (height(x->left) >= 2 + height(x->right)) {
      if (height(x->left->left) >= height(x->left->right))
        right_rotate(t, x);
      else {
        left_rotate(t, x->left);
        right_rotate(t, x);
      }
    } else if (height(x->right) >= 2 + height(x->left)) {
      if (height(x->right->right) >= height(x->right->left))
        left_rotate(t, x);
      else {
        right_rotate(t, x->right);
        left_rotate(t, x);
      }
    }
    if (x == x->parent) {
      exit(1);
    }
    x = x->parent;
  }
}

/* x->right should not be NULL */
void left_rotate(AVLTree *t, Node *x) {
  Node *y = x->right;
  assert(y != NULL);
  x->right = y->left;
  if (y->left != NULL)
    y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == NULL)
    t->root = y;
  else if (x == y->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
  update_height(x);
  update_height(y);
}

/* y->left should not be NULL */
void right_rotate(AVLTree *t, Node *y) {
  Node *x = y->left;
  assert(x != NULL);

  y->left = x->right;
  if (x->right != NULL)
    x->right->parent = y;

  if (y->parent == NULL)
    t->root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  x->right = y;
  y->parent = x;
  update_height(y);
  update_height(x);
}

void verify_avl_property(Node *root) {
  if (root == NULL)
    return;
  int s1 = height(root->left);
  int s2 = height(root->right);
  if (abs(s1 - s2) >= 2) {
    printf("verifying avl property failed at node: %d\n", root->data);
    exit(1);
  }
  verify_avl_property(root->left);
  verify_avl_property(root->right);
}

/* -------------- begin avl.h functions ---------- */

Node *mknode(int data) {
  Node *n = malloc(sizeof(Node));
  n->data = data;
  n->left = NULL;
  n->right = NULL;
  n->parent = NULL;
  n->height = 0;
  return n;
}

AVLTree *mktree() {
  AVLTree *t = malloc(sizeof(AVLTree));
  t->root = NULL;
  return t;
}

void traverse(Node *root) {
  if (root != NULL) {
    traverse(root->left);
    printnode(root);
    traverse(root->right);
  }

  fflush(stdout);
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
  rebalance(t, z);
  return z;
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
  rebalance(t, z->parent);
  free_node(z);
}

void test() {
  AVLTree *my = mktree();

  for (int i = 0; i < 10; i++) {
    insert(my, mknode(rand()));
  }

  // traverse(my->root);

  verify_avl_property(my->root);

  free_tree(my);
}

int main() {
  srand(time(NULL));

  test();
}

// vim: shiftwidth=2:softtabstop=2:expandtab
