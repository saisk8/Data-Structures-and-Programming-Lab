#include <stdio.h>

/*
Bubble sort
Worst case performance: O(n^2)
Best case performance: Ω(n)
Average performance: Θ(n^2)
Worst case space complexity: O(1)
*/

void bubble_sort(int arr[], int n) {
  int temp;
  int i = 0;
  int j = 0;

  while (i < n) {
    j = 0;
    while (j < i) {
      if (arr[j] > arr[i]) {
        temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
      j++;
    }
    i++;
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
  bubble_sort(arr, n);
  for (i = 0; i < n; i++) fprintf(q, "%d\n", arr[i]);
  fclose(p);
  fclose(q);
  return 0;
}