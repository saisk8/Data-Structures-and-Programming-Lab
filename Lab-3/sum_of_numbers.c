#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  double n, temp;
  printf("Enter a natural number: ");
  if (!scanf("%lf", &n)) {
    printf("Please enter a valid natural number...\n");
    exit(0);
  }
  temp = n - (int)n;
  if (temp) {
    printf("Please enter a valid natural number...\n");
    exit(0);
  }
  printf("The Sum = %ld\n", (long int)((n * (n + 1)) / 2));
  return 0;
}
