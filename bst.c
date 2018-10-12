#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	struct node *left, *right;
};

struct node *addElement(struct node *root, int e) {
	if (root == NULL) {
		root = (struct node*)malloc(sizeof(struct node));
		root->key = e;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	struct node *curr = root, *prev = NULL;
	while (curr != NULL) {
		if (curr->key == e) return root;
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
	} else  if (e < prev->key){
		prev->left = (struct node *)malloc(sizeof(struct node));
		prev->left->key = e;
		prev->left->right = prev->left->left = NULL;
	}
	return root;
}

void preorder(struct node *root) {
	if (!root) return;
	printf("%d ", root->key);
	preorder(root->left);
	preorder(root->right);
}

void inOrder(struct node *root, FILE *q) {
	if (!root) return;
	inOrder(root->left, q);
	fprintf(q, "%d ", root->key);
	inOrder(root->right, q);
}

void postOrder(struct node *root, FILE *q) {
	if (!root) return;
	postOrder(root->left, q);
	postOrder(root->right, q);
	fprintf(q, "%d", root->key, q);
}

int main() {
	int n;
	FILE *p = fopen("input.txt", "r"), *q;
	q = fopen("output.txt", "w");
	struct node *root = NULL;
	fscanf(p, "%d", &n);
	int elements[n];
	// int elements[] = {50, 30, 60, 10, 25, 70, 40};
	// int n = sizeof(elements) / sizeof(elements[0]);
	for (int i = 0; i < n; i++) {
		fscanf(p, "%d", &elements[i]);
		root = addElement(root, elements[i]);
	}
	printf("Pre-Order tree traversal: ");
	preorder(root);
	fprintf(q, "In-Order tree traversal: ");
	inOrder(root, q);
	printf("\n");
	return 0;
}
