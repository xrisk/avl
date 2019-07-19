typedef struct Node {
  struct Node *parent, *left, *right;
  int data;
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

void rmnode(Node *x);
void rmtree(AVLTree *x);
