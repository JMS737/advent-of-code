#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eval(int a, int b, int *direction) {
  if (a == b) {
    return 0;
  }

  int diff = b - a;
  int absDiff = abs(diff);
  int dir = diff / absDiff;

  if (absDiff > 3) {
    return 0;
  }

  if (!*direction) {
    *direction = dir;
  } else {
    if (*direction != dir) {
      return 0;
    }
  }

  return 1;
}

int is_valid(char *line) {
  int direction = 0;
  int next, prev;
  char *token = strtok(line, " ");

  if (token != NULL) {
    prev = atoi(token);
    token = strtok(NULL, " ");
  }

  while (token != NULL) {
    next = atoi(token);

    if (!eval(prev, next, &direction)) {
      return 0;
    }
    prev = next;
    token = strtok(NULL, " ");
  }

  return 1;
}

int main() {
  FILE *input = fopen("../input.txt", "r");

  int safe = 0, unsafe = 0;
  char line[100];
  char valid;

  while (fgets(line, sizeof(line), input) != NULL) {
    valid = is_valid(line);

    if (valid) {
      safe++;
    } else {
      unsafe++;
    }
  }

  printf("%i safe / %i unsafe\n", safe, unsafe);

  return 0;
}
