#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
  int num;
  struct Node *next;
};

void insert(struct Node **, FILE *, int *);
void display(struct Node *);
int winner(struct Node **, int);

int main() {
  struct Node *head = NULL;
  int survive, tests, seed;
  FILE *p = fopen("input2.txt", "r");
  fscanf(p, "%d", &tests);
  while (tests--) {
    insert(&head, p, &seed);
    // printf("The persons in circular list are:\n");
    display(head);
    // printf("Enter the seed: ");
    survive = winner(&head, seed);
    printf("The person to survive is : %d\n", survive);
    free(head);
  }
  return 0;
}

int countNodes(struct Node *head) {
  struct Node *temp = head;
  int result = 0;
  if (head != NULL) {
    do {
      temp = temp->next;
      result++;
    } while (temp != head);
  }

  return result;
}

int winner(struct Node **head, int seed) {
  struct Node *p, *q;
  int i;

  q = p = *head;
  while (p->next != p) {
    srand(seed);
    int k = (rand() % countNodes(p)) + 1;
    for (i = 0; i < k - 1; i++) {
      q = p;
      p = p->next;
    }
    q->next = p->next;
    printf("%d has been killed.\n", p->num);
    free(p);
    p = q->next;
    display(p);
  }
  *head = p;

  return (p->num);
}

void insert(struct Node **head, FILE *p, int *seed) {
  struct Node *temp, *rear;
  int a, ch;
  // printf("Enter the number of nodes: ");
  fscanf(p, "%d", &a);
  while (a--) {
    // printf("Enter the number: ");
    fscanf(p, "%d %d", &ch, seed);
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->num = a;
    temp->next = NULL;
    if (*head == NULL) {
      *head = temp;
    } else {
      rear->next = temp;
    }
    rear = temp;
  }
  rear->next = *head;
}

void display(struct Node *head) {
  struct Node *temp;
  temp = head;
  printf("%d   ", temp->num);
  temp = temp->next;
  while (head != temp) {
    printf("%d   ", temp->num);
    temp = temp->next;
  }
  printf("\n");
}
