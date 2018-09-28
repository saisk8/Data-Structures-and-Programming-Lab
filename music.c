#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

int deleteCount = 0, n;

struct node {
	int key;
	int visited;
	struct node *next;
};

struct node* insert(struct node *rear, int key) {
	if (rear == NULL) {
		rear = (struct node *)malloc(sizeof(struct node));
		rear->key = key;
		rear->visited = 0;
		rear->next = rear;
		return rear;
	}
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = key;
	rear->visited = 0;
	temp->next = rear->next;
	rear->next = temp;
	return rear;
}

struct node *deleteAndReplace(struct node *ptr, struct node *rear) {
	if (ptr == rear && ptr->visited == 1 && deleteCount == n - 1) {
		rear = rear->next;
	}
	if (ptr->visited == 1 && deleteCount == n - 1) {
		ptr->key = ptr->next->key;
		ptr->visited = ptr->next->visited;
		struct node *t = ptr->next;
		ptr->next = ptr->next->next;
		free(ptr);
		return rear;
	}
	if (ptr->visited == 1 && deleteCount != n - 1) {
		return rear;
	}
	if (ptr->visited == 0 && deleteCount < n - 1) {
		ptr->visited = 1;
		deleteCount++;
		srand(time(NULL));
		ptr->key = rand();
	}
	return rear;
}

struct node *deleteNode(struct node *rear, int pos) {
	int index = 0;
	struct node *ptr = rear;
	if (rear == NULL) {
		printf("There has been an error\n");
		exit(0);
	}
	else if (rear->next == rear) {
		return rear;
	}
	while (pos != index++) {
		ptr = ptr->next;
	}
	return deleteAndReplace(ptr, rear);
}

void display(struct node *rear) {
	struct node *ptr = rear;
	printf("The members are: \n");
	do {
		printf("%d ", ptr->key);
		ptr = ptr->next;
	} while(ptr != rear);
	printf("\n");
}

int winner(struct node *rear) {
	int count = n;
	while (rear->next != rear && deleteCount != n - 1) {
		srand(time(NULL));
		rear = deleteNode(rear, rand() % count);
		display(rear);
	}
	return rear->key;
}

int main() {
	struct node *rear = NULL;
	int key;
	printf("Enter the number of participants: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("Enter the key: ");
		scanf("%d", &key);
		rear = insert(rear, key);
	}
	printf("The winner is: %d\n", winner(rear));
	return 0;
}
