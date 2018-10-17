#include <stdio.h>
#include <stdlib.h>

struct node {
  int key;
  struct node *left, *right;
};

struct node *addElement(struct node *root, char e) {
  if (root == NULL) {
    root = (struct node *)malloc(sizeof(struct node));
    root->key = e;
    root->left = NULL;
    root->right = NULL;
    return root;
  }
  struct node *curr = root, *prev = NULL;
  while (curr != NULL) {
    if (curr->key == e)
      return root;
    if (curr->key > e) {
      prev = curr;
      curr = curr->left;
      continue;
    }
    if (curr->key < e) {
      prev = curr;
      curr = curr->right;
      continue;
    }
  }
  if (e > prev->key) {
    prev->right = (struct node *)malloc(sizeof(struct node));
    prev->right->key = e;
    prev->right->left = prev->right->right = NULL;
  } else if (e < prev->key) {
    prev->left = (struct node *)malloc(sizeof(struct node));
    prev->left->key = e;
    prev->left->right = prev->left->left = NULL;
  }
  return root;
}

void preorder(struct node *root, FILE *q) {
  if (!root)
    return;

  fprintf(q, "%d ", root->key);
  preorder(root->left, q);
  preorder(root->right, q);
}

void inOrder(struct node *root, FILE *q) {
  if (!root)
    return;
  inOrder(root->left, q);
  fprintf(q, "%d ", root->key);
  inOrder(root->right, q);
}

void postOrder(struct node *root, FILE *q) {
  if (!root)
    return;
  postOrder(root->left, q);
  postOrder(root->right, q);
  fprintf(q, "%d ", root->key);
}

int main() {
  int n, testCases;
  FILE *p = fopen("input.txt", "r"), *q;
  q = fopen("output.txt", "w");
  struct node *root = NULL;
  fscanf(p, "%d", &testCases);
  for (size_t i = 0; i < testCases; i++) {
    root = NULL;
    fprintf(q, "\nTest Case %ld:\n", i + 1);
    fscanf(p, "%d", &n);
    if (n < 0) {
      fprintf(q, "\n%s", "Number of elements can't be negative");
      continue;
    } else if (n == 0) {
      fprintf(q, "\n%s", "No elements in the binary search tree");
      continue;
    }
    int elements[n];
    for (int j = 0; j < n; j++) {
      fscanf(p, "%d", &elements[j]);
      root = addElement(root, elements[j]);
    }
    fprintf(q, "\nPre-Order traversal: ");
    preorder(root, q);
    fprintf(q, "\nIn-Order traversal: ");
    inOrder(root, q);
    fprintf(q, "\nPost-Order traversal: ");
    postOrder(root, q);
    fprintf(q, "\n");
  }
  return 0;
}
