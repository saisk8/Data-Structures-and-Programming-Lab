#include <stdio.h>
#include <stdlib.h>
/*
Selection sort
Worst case performance: O(n^2)
Best case performance: Ω(n^2)
Average performance: Θ(n^2)
Worst case space complexity: O(1)
*/

void selection_sort(int arr[], int n) {
  int i, j;

  for (j = 0; j < n - 1; j++) {
    int iMin = j;

    for (i = j + 1; i < n; i++) {
      if (arr[i] < arr[iMin]) {
        iMin = i;
      }
    }

    if (iMin != j) {
      int temp = arr[j];
      arr[j] = arr[iMin];
      arr[iMin] = temp;
    }
  }
}

int main() {
  int n, i;
  FILE *p, *q;
  p = fopen("input.txt", "r");
  q = fopen("output.txt", "w");
  // Read the number of elements
  fscanf(p, "%d", &n);
  int arr[n];
  for (i = 0; i < n; i++) {
    fscanf(p, "%d", &arr[i]);
  }
  selection_sort(arr, n);
  for (i = 0; i < n; i++) fprintf(q, "%d\n", arr[i]);
  fclose(p);
  fclose(q);
  return 0;
}