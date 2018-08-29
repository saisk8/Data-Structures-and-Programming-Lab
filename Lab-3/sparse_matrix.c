// C program for Sparse Matrix Representation
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
  double value;
  int row_position;
  int column_postion;
  struct Node *next;
};

void create_new_node(struct Node **start, double non_zero_element,
                     int row_index, int column_index) {
  struct Node *temp, *r;
  temp = *start;
  if (temp == NULL) {
    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->value = non_zero_element;
    temp->row_position = row_index;
    temp->column_postion = column_index;
    temp->next = NULL;
    *start = temp;

  } else {
    while (temp->next != NULL)
      temp = temp->next;

    r = (struct Node *)malloc(sizeof(struct Node));
    r->value = non_zero_element;
    r->row_position = row_index;
    r->column_postion = column_index;
    r->next = NULL;
    temp->next = r;
  }
}

void ShowRep(struct Node *start) {
  struct Node *t, *r, *s;
  t = r = s = start;
  if (!start) {
    printf("There are no non-zero elements in the list(the input was a Null "
           "Matrix)\n");
    return;
  }
  printf("Row: ");
  while (t != NULL) {

    printf("%-6d ", t->row_position);
    t = t->next;
  }
  printf("\n");

  printf("Col: ");
  while (r != NULL) {
    printf("%-6d ", r->column_postion);
    r = r->next;
  }
  printf("\n");
  printf("Val: ");
  while (s != NULL) {
    double fractpart;
    fractpart = s->value - (int)s->value;
    // printf("%lf\n", fractpart);
    if (fractpart)
      printf("%-.4lf ", s->value);
    else
      printf("%-4.0lf ", s->value);
    s = s->next;
  }
  printf("\n");
}

int main() {
  int n, m;
  printf("Enter the number of rows: ");
  scanf("%d", &n);
  printf("Enter the number of colums: ");
  scanf("%d", &m);
  double sparseMatric[n][m];
  /* Start with the empty list */
  printf("Enter the matrix: \n");
  struct Node *start = NULL;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (!scanf("%lf", &sparseMatric[i][j])) {
        printf("Invalid input, enter a valid number...\n");
        exit(0);
      }
      if (sparseMatric[i][j] != 0)
        create_new_node(&start, sparseMatric[i][j], i, j);
    }

  ShowRep(start);

  return 0;
}
