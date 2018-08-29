// Fibonacci Series using Recursion
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int fib(int n) {
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int main() {
  double n, temp;
  int i = 0;
  printf("%s", "Enter a number: ");
  if (!scanf("%lf", &n)) {
    printf("%s\n", "Invalid input, please enter a valid integer");
    exit(0);
  }
  temp = n - (int)n;
  if (temp) {
    printf("%s\n", "Invalid input, please enter an integer");
    exit(0);
  }
  printf("Series: ");
  while (i < n) {
    printf("%d ", fib(i++));
  }
  printf("\n");
  return 0;
}
