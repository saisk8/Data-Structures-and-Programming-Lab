#include <stdio.h>
#include <stdlib.h>

/*
Quick sort
Worst case performance: O(n^2)
Best case performance: Ω(n)
Average performance: Θ(n log(n))
Worst case space complexity: O(n)
*/

void quickSort(int arr[], int first_index, int last_index) {
  // declaring index variables
  int pivotIndex, temp, index_a, index_b;

  if (first_index < last_index) {
    // assigning first element index as pivot element
    pivotIndex = first_index;
    index_a = first_index;
    index_b = last_index;

    // Sorting in Ascending order with quick sort
    while (index_a < index_b) {
      while (arr[index_a] <= arr[pivotIndex] && index_a < last_index) {
        index_a++;
      }
      while (arr[index_b] > arr[pivotIndex]) {
        index_b--;
      }

      if (index_a < index_b) {
        // Swapping operation
        temp = arr[index_a];
        arr[index_a] = arr[index_b];
        arr[index_b] = temp;
      }
    }

    // At the end of first iteration, swap pivot element with index_b element
    temp = arr[pivotIndex];
    arr[pivotIndex] = arr[index_b];
    arr[index_b] = temp;

    // Recursive call for quick sort, with partitioning
    quickSort(arr, first_index, index_b - 1);
    quickSort(arr, index_b + 1, last_index);
  }
}

int main() {
  int n, i;
  FILE *p, *q;
  p = fopen("input.txt", "r");
  q = fopen("output.txt", "w");
  // Read the number of elements
  fscanf(p, "%d", &n);
  int a[n + 1];
  for (i = 1; i <= n; i++) {
    fscanf(p, "%d", &a[i]);
  }
  quickSort(a, 1, n);
  for (i = 1; i <= n; i++) fprintf(q, "%d\n", a[i]);
  fclose(p);
  fclose(q);
  return 0;
}