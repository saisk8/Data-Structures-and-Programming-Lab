#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int is_negative = 0;

int stringCompare(const char *s1, const char *s2) {
  int length = strlen(s1) + strlen(s1);
  char p1[length], p2[length];
  strcpy(p1, s1);
  strcat(p1, s2);
  strcpy(p2, s2);
  strcat(p2, s1);
  return strcmp(p1, p2);
}

void swap_str_ptrs(char const **arg1, char const **arg2) {
  const char *tmp = *arg1;
  *arg1 = *arg2;
  *arg2 = tmp;
}

void quicksort_strs(char const *args[], unsigned int len, int is_negative) {
  unsigned int i, pvt = 0;
  if (len <= 1)
    return;
  swap_str_ptrs(args + ((unsigned int)rand() % len), args + len - 1);
  for (i = 0; i < len - 1; ++i) {
    if (is_negative) {
      if (stringCompare(args[i], args[len - 1]) < 0)
        swap_str_ptrs(args + i, args + pvt++);
    } else {
      if (stringCompare(args[i], args[len - 1]) > 0)
        swap_str_ptrs(args + i, args + pvt++);
    }
  }
  swap_str_ptrs(args + pvt, args + len - 1);
  quicksort_strs(args, pvt++, is_negative);
  quicksort_strs(args + pvt, len - pvt, is_negative);
}

char *inputString(FILE *f, size_t size) {
  char *str;
  int ch;
  size_t len = 0;
  str = (char *)realloc(NULL, sizeof(char) * size); // size is start size
  if (!str)
    return str;
  while (EOF != (ch = fgetc(f)) && (ch != '\n')) {
    if (ch == '-') {
      is_negative = 1;
      continue;
    }
    str[len++] = ch;
    if (len == size) {
      str = (char *)realloc(str, sizeof(char) * (size += 5));
      if (!str)
        return str;
    }
  }
  str[len++] = '\0';

  return (char *)realloc(str, sizeof(char) * len);
}

void print_largest(FILE *f, char const *args[], unsigned len) {
  unsigned i = 0;
  if (is_negative) {
    fputc('-', f);
  }
  while (fputs(args[i++], f) && i < len)
    ;
  fprintf(f, "\n\n");
}

int main(int argc, char const *argv[]) {

  long int test_cases, count = 0, n;
  FILE *input_file = fopen("largest-input.txt", "r"),
       *output_file = fopen("largest-output.txt", "w");
  fscanf(input_file, "%ld", &test_cases);
  while (test_cases--) {
    // printf("%s\n", "Step - 1");
    fprintf(output_file, "Test Case %ld: \n", ++count);
    fscanf(input_file, "%ld\n", &n);
    const char **input = (const char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
      //  printf("%s ", "Ok");
      input[i] = inputString(input_file, 10);
    }
    // logic
    srand((unsigned)time(NULL));
    quicksort_strs(input, n, is_negative);
    print_largest(output_file, input, n);
    // end logic
    for (int i = 0; i < n; i++) {
      free((void *)input[i]);
    }
    free(input);
  }
  return 0;
}
