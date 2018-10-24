#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Quick sort
Worst case performance: O(n^2)
Best case performance: Ω(n)
Average performance: Θ(n log(n))
Worst case space complexity: O(n)
*/

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

void quicksort_strs(char const *args[], unsigned int len) {
  unsigned int i, pvt = 0;
  if (len <= 1) return;
  swap_str_ptrs(args + ((unsigned int)rand() % len), args + len - 1);
  for (i = 0; i < len - 1; ++i) {
    if (strCmp(args[i], args[len - 1]) < 0)
      swap_str_ptrs(args + i, args + pvt++);
  }
  swap_str_ptrs(args + pvt, args + len - 1);
  quicksort_strs(args, pvt++);
  quicksort_strs(args + pvt, len - pvt);
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

void print(FILE *out, const char **strs, int n) {
  for (int i = 0; i < n; i++) {
    fprintf(out, "%s\n", strs[i]);
  }
  fprintf(out, "\n\n");
}

int main(int argc, char const *argv[]) {
  long int test_cases, count = 0, n;
  FILE *input_file = fopen("input.txt", "r"),
       *output_file = fopen("output.txt", "w");
  fscanf(input_file, "%ld", &test_cases);
  while (test_cases--) {
    fprintf(output_file, "Test Case %ld: \n", ++count);
    fscanf(input_file, "%ld\n", &n);
    const char **input = (const char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
      input[i] = inputString(input_file, 10);
    }
    // logic
    srand((unsigned)time(NULL));
    quicksort_strs(input, n);
    print(output_file, input, n);
    // end logic
    for (int i = 0; i < n; i++) {
      free((void *)input[i]);
    }
    free(input);
  }
  return 0;
}