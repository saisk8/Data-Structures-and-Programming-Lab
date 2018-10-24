/*
Merge sort
Worst case performance: O(n log(n))
Best case performance: Ω(n log(n))
Average performance: Θ(n log(n))
Worst case space complexity: O(n)
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int strCmp(const char *s1, const char *s2) {
  if (*s1 == '-' && *s2 != '-') return -1;
  if (*s1 != '-' && *s2 == '-') return 1;
  if (*s1 == '-' && *s2 == '-') return strCmp(++s1, ++s2) * -1;
  for (;;) {
    if (*s2 == '\0')
      return *s1 != '\0';
    else if (*s1 == '\0')
      return 1;
    else if (!(isdigit(*s1) && isdigit(*s2))) {
      if (*s1 != *s2)
        return (int)*s1 - (int)*s2;
      else
        (++s1, ++s2);
    } else {
      char *lim1, *lim2;
      unsigned long n1 = strtoul(s1, &lim1, 10);
      unsigned long n2 = strtoul(s2, &lim2, 10);
      if (n1 > n2)
        return 1;
      else if (n1 < n2)
        return -1;
      s1 = lim1;
      s2 = lim2;
    }
  }
}

void swap_str_ptrs(char const **arg1, char const **arg2) {
  const char *tmp = *arg1;
  *arg1 = *arg2;
  *arg2 = tmp;
}

char *inputString(FILE *f, size_t size) {
  char *str;
  int ch;
  size_t len = 0;
  str = (char *)realloc(NULL, sizeof(char) * size);  // size is start size
  if (!str) return str;
  while (EOF != (ch = fgetc(f)) && (ch != '\n')) {
    str[len++] = ch;
    if (len == size) {
      str = (char *)realloc(str, sizeof(char) * (size += 5));
      if (!str) return str;
    }
  }
  str[len++] = '\0';

  return (char *)realloc(str, sizeof(char) * len);
}

void print(FILE *out, char **strs, int n) {
  for (int i = 0; i < n; i++) {
    fprintf(out, "%s\n", strs[i]);
  }
  fprintf(out, "\n\n");
}

void Merge(char *arr[], int low, int mid, int high) {
  int nL = mid - low + 1;
  int nR = high - mid;

  char **L = malloc(sizeof(char *) * nL);
  char **R = malloc(sizeof(char *) * nR);
  int i;
  for (i = 0; i < nL; i++) {
    L[i] = malloc(sizeof(arr[low + i]));
    strcpy(L[i], arr[low + i]);
  }
  for (i = 0; i < nR; i++) {
    R[i] = malloc(sizeof(arr[mid + i + 1]));
    strcpy(R[i], arr[mid + i + 1]);
  }
  int j = 0, k;
  i = 0;
  k = low;
  while (i < nL && j < nR) {
    if (strCmp(L[i], R[j]) < 0)
      strcpy(arr[k++], L[i++]);
    else
      strcpy(arr[k++], R[j++]);
  }
  while (i < nL) strcpy(arr[k++], L[i++]);
  while (j < nR) strcpy(arr[k++], R[j++]);
}

int mergesort_r(int left, int right, char **list)  // Overloaded portion
{
  if (right - left <= 1) {
    return 0;
  }

  int left_start = left;
  int left_end = (left + right) / 2;
  int right_start = left_end;
  int right_end = right;

  mergesort_r(left_start, left_end, list);

  mergesort_r(right_start, right_end, list);

  Merge(list, left_start, left_end, right_end);
}

int main(int argc, char const *argv[]) {
  long int test_cases, count = 0, n;
  FILE *input_file = fopen("input.txt", "r"),
       *output_file = fopen(".output.txt", "w");
  fscanf(input_file, "%ld", &test_cases);
  while (test_cases--) {
    fprintf(output_file, "Test Case %ld: \n", ++count);
    fscanf(input_file, "%ld\n", &n);
    char **input = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
      input[i] = inputString(input_file, 10);
    }
    // logic
    srand((unsigned)time(NULL));
    mergesort_r(0, n - 1, input);
    print(output_file, input, n);
    // end logic
    for (int i = 0; i < n; i++) {
      free((void *)input[i]);
    }
    free(input);
  }
  return 0;
}