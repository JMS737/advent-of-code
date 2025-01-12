#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *input = fopen("../input.txt", "r");

  int safe = 0, unsafe = 0;
  char line[100];
  int line_max;
  int next, prev, diff, prevDiff;
  char valid;

  char userInput[1];

  while (fgets(line, sizeof(line), input) != NULL) {
    // printf("%s", line);
    valid = 1;
    prevDiff = 0;

    char *token = strtok(line, " ");

    if (token != NULL) {
      prev = atoi(token);
      // printf("start %i\n", prev);
      token = strtok(NULL, " ");
    }

    while (token != NULL) {
      next = atoi(token);

      diff = prev - next;

      // printf("%i to %i diff %i ", prev, next, diff);
      if (prev == next || abs(diff) > 3
        || (prevDiff < 0 && diff > 0) || (prevDiff > 0 && diff < 0)) {
        // printf("invalid\n");
        valid = 0;
        break;
      }

      // printf("valid\n");
      prev = next;
      prevDiff = diff;
      token = strtok(NULL, " ");
    }

    if (valid) {
      safe++;
      // printf("safe S%i U%i\n", safe, unsafe);
    } else {
      unsafe++;
      // printf("unafe S%i U%i\n", safe, unsafe);
    }

    // scanf("%s", userInput);
  }

  printf("%i safe / %i unsafe\n", safe, unsafe);

  return 0;
}
