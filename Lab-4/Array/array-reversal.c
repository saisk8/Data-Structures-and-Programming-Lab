#include <stdio.h>
#include <stdlib.h>

char *inputString(FILE *f, size_t size) {
  char *str;
  int ch;
  size_t len = 0;
  str = (char *)realloc(NULL, sizeof(char) * size);
  if (!str)
    return str;
  while (EOF != (ch = fgetc(f)) && (ch != '\n')) {
    // if (ch == '\n')
    //   continue;
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

int main(int argc, char const *argv[]) {
  long int test_cases, count = 0, n, k;
  FILE *input_file = fopen("array-input.txt", "r"),
       *output_file = fopen("array-output.txt", "w");
  fscanf(input_file, "%ld", &test_cases);
  while (test_cases--) {
    // printf("%s\n", "Step - 1");
    fprintf(output_file, "Test Case %ld: \n", ++count);
    fscanf(input_file, "%ld%ld\n", &n, &k);
    k = (k % n + n) % n;
    // printf("%ld\n", k);
    char **input = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
      //  printf("%s ", "Ok");
      input[i] = inputString(input_file, 10);
    }
    // printf("\n");
    for (int i = n - k; i < n; i++) {
      // printf("%d ", i);
      // printf("%s ", input[i]);
      fprintf(output_file, "%s ", input[i]);
    }
    for (int i = 0; i < n - k; i++)
      fprintf(output_file, "%s ", input[i]);
    fprintf(output_file, "\n\n");
    for (int i = 0; i < n; i++) {
      free(input[i]);
    }
    free(input);
  }
  return 0;
}
