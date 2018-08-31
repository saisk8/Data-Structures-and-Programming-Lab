#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT 1
#define LONG 2
#define ULONG 3
#define OVERFLOW -1

int determinInputSize(const char *);

struct DataType {
  int size, intValue, error;
  long int longValue;
  unsigned long int ulongValue;
};
typedef struct DataType Data;

Data info;
Data *determiner(const char *s) {
  info.size = determinInputSize(s);
  switch (determinInputSize(s)) {
  case INT:
    info.size = INT;
    sscanf(s, "%d", &info.intValue);
  case LONG:
    info.size = LONG;
    sscanf(s, "%ld", &info.longValue);
  case ULONG:
    info.size = ULONG;
    sscanf(s, "%lu", &info.ulongValue);
  case OVERFLOW:
    info.size = OVERFLOW;
    info.error = 1;
  default:
    exit(0);
  }
  return &info;
}

int determinInputSize(const char *s) {
  short int isPositive = 1;
  char intValue[30], longValue[30], ulongValue[30];
  if (s[0] == '-')
    isPositive = 0;
  if (isPositive) {
    const int intLength = sprintf(intValue, "%d", INT_MAX);
    const int longLength = sprintf(longValue, "%ld", LONG_MAX);
    const int ulongLength = sprintf(ulongValue, "%lu", ULONG_MAX);
    const int inputLength = strlen(s);
    if (inputLength < intLength) {
      return INT;
    } else if (inputLength == intLength) {
      if (strcmp(s, intValue) > 0)
        return LONG;
      else
        return INT;
    } else if (inputLength > intLength && inputLength < longLength) {
      return LONG;
    } else if (inputLength == longLength) {
      if (strcmp(s, longValue) > 0)
        return ULONG;
      else
        return LONG;
    } else if (inputLength > longLength && inputLength < ulongLength) {
      return ULONG;
    } else if (inputLength == ulongLength) {
      if (strcmp(s, ulongValue) > 0) {
        return OVERFLOW;
      } else
        return LONG;
    } else {
      return OVERFLOW;
    }
  } else {
    const int intLength = sprintf(intValue, "%d", INT_MIN);
    const int longLength = sprintf(longValue, "%ld", LONG_MIN);
    const int inputLength = strlen(s);
    if (inputLength < intLength) {
      return INT;
    } else if (inputLength == intLength) {
      if (strcmp(s, intValue) > 0)
        return LONG;
      else
        return INT;
    } else if (inputLength > intLength && inputLength < longLength) {
      return LONG;
    } else if (inputLength == longLength) {
      if (strcmp(s, longValue) > 0)
        return OVERFLOW;
      else
        return LONG;
    } else {
      return OVERFLOW;
    }
  }
}

char *inputString(FILE *f, size_t size) {
  char *str;
  int ch;
  size_t len = 0;
  str = (char *)realloc(NULL, sizeof(char) * size); // size is start size
  if (!str)
    return str;
  while (EOF != (ch = fgetc(f)) && (ch != '\n')) {
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
