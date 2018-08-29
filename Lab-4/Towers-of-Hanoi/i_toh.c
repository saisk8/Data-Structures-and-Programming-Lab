#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
  unsigned capacity;
  int top;
  int *array;
};

struct Stack *createStack(unsigned capacity) {
  struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (int *)malloc(stack->capacity * sizeof(int));
  return stack;
}

int isFull(struct Stack *stack) { return (stack->top == stack->capacity - 1); }

int isEmpty(struct Stack *stack) { return (stack->top == -1); }

void push(struct Stack *stack, int item) {
  if (isFull(stack))
    return;
  stack->array[++stack->top] = item;
}

int pop(struct Stack *stack) {
  if (isEmpty(stack))
    return INT_MIN;
  return stack->array[stack->top--];
}

void moveDisk(char fromPeg, char toPeg, int disk, FILE *f) {
  fprintf(f, "Move the disk %d from \'%c\' to \'%c\'\n", disk, fromPeg, toPeg);
}

void moveDisksBetweenTwoPoles(struct Stack *src, struct Stack *dest, char s,
                              char d, FILE *f) {
  int pole1TopDisk = pop(src);
  int pole2TopDisk = pop(dest);

  if (pole1TopDisk == INT_MIN) {
    push(src, pole2TopDisk);
    moveDisk(d, s, pole2TopDisk, f);
  }

  else if (pole2TopDisk == INT_MIN) {
    push(dest, pole1TopDisk);
    moveDisk(s, d, pole1TopDisk, f);
  }

  else if (pole1TopDisk > pole2TopDisk) {
    push(src, pole1TopDisk);
    push(src, pole2TopDisk);
    moveDisk(d, s, pole2TopDisk, f);
  }

  else {
    push(dest, pole2TopDisk);
    push(dest, pole1TopDisk);
    moveDisk(s, d, pole1TopDisk, f);
  }
}

void tohIterative(int num_of_disks, struct Stack *src, struct Stack *aux,
                  struct Stack *dest, FILE *p) {
  int i, total_num_of_moves;
  char s = 'S', d = 'D', a = 'A';

  if (num_of_disks % 2 == 0) {
    char temp = d;
    d = a;
    a = temp;
  }
  total_num_of_moves = pow(2, num_of_disks) - 1;

  for (i = num_of_disks; i >= 1; i--)
    push(src, i);

  for (i = 1; i <= total_num_of_moves; i++) {
    if (i % 3 == 1)
      moveDisksBetweenTwoPoles(src, dest, s, d, p);

    else if (i % 3 == 2)
      moveDisksBetweenTwoPoles(src, aux, s, a, p);

    else if (i % 3 == 0)
      moveDisksBetweenTwoPoles(aux, dest, a, d, p);
  }
}

int main() {
  int test_cases, count = 0;
  float n;
  struct Stack *src, *dest, *aux;
  FILE *input_file = fopen("hanoi-input.txt", "r"),
       *output_file = fopen("hanoi-output.txt", "w");
  // printf("Enter the number of disks: ");
  fscanf(input_file, "%d", &test_cases);
  while (test_cases--) {
    fprintf(output_file, "Test Case %d: \n", ++count);
    if (!fscanf(input_file, "%f", &n)) {
      fprintf(output_file, "Please enter a valid integer...\n\n");
      printf("%f\n", n);
      continue;
    }
    if (n - (int)n) {
      fprintf(output_file, "Please enter a valid integer...\n\n");
      continue;
    }
    if (n > 0) {
      src = createStack(n);
      aux = createStack(n);
      dest = createStack(n);
      fprintf(output_file, "Number of moves = %.0lf\n", pow(2, n) - 1);
      tohIterative(n, src, aux, dest, output_file);
      fprintf(output_file, "\n\n");
    } else {
      fprintf(output_file, "The number of disks must be greater than 0\n");
    }
  }
  return 0;
}
