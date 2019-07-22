#include "avl.h"
#include <assert.h>
#include <stdio.h>

int main() {

  AVLTree *my = mktree();

  int arr[] = {100, 95, 23, 76, 1, 1, 46, 74, 15, 18, 11, 54};
  int sz = sizeof(arr) / sizeof(int);

  for (int i = 0; i < sz; i++) {
    insert(my, mknode(arr[i]));
    // traverse(my->root);
  }

  traverse(my->root);
  verify_avl_property(my->root);

  assert(tree_min(my->root)->data == 1);
  assert(successor(find(my->root, 11))->data == 15);
  assert(predecessor(find(my->root, 100))->data == 95);

  insert(my, mknode(105));

  assert(tree_max(my->root)->data == 105);
  assert(successor(find(my->root, 100))->data == 105);

  delete_node(my, find(my->root, 95));
  assert(predecessor(find(my->root, 100))->data == 76);

  free_tree(my);
}
