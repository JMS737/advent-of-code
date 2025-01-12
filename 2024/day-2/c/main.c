#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAMPENER_ENABLED 1
#define LINE_SIZE 100

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

int is_valid(const char *line) {
  int direction = 0;
  int next, prev;
  char line_copy[LINE_SIZE];

  strcpy(line_copy, line);
  char *token = strtok(line_copy, " ");

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

const char *remove_level(char *new_line, const char *line, int skip) {
  int i = 0;
  int n = 0;
  int iToken = 0;

  while (i < LINE_SIZE) {

    if (iToken != skip || line[i] == '\n') {
      new_line[n] = line[i];
      n++;
    }

    if (line[i] == '\n' || line[i] == 0) {
      // if skip is more then the number of tokens in the line, return null to
      // indicate invalid op
      if (skip > iToken) {
        return NULL;
      }

      break;
    }

    if (line[i] == ' ') {
      iToken++;
    }

    i++;
  }

  if (new_line[n - 2] == ' ') {
    new_line[n - 2] = '\n';
    new_line[n -1] = 0;
  }

  while (n < LINE_SIZE) {
    new_line[n] = 0;
    n++;
  }

  return new_line;
}

int is_valid_dampened(const char *line) {
  int skip = 0;
  char new_line[LINE_SIZE];

  while (remove_level(new_line, line, skip) != NULL) {
    if (is_valid(new_line)) {
      return 1;
    }

    skip++;
  }

  return 0;
}

int main() {

  FILE *input = fopen("../input.txt", "r");

  int safe = 0, unsafe = 0;
  char line[LINE_SIZE];
  char valid;

  while (fgets(line, sizeof(line), input) != NULL) {
    valid = is_valid(line);

    if (DAMPENER_ENABLED && !valid) {
      valid = is_valid_dampened(line);
    }
    if (valid) {
      safe++;
    } else {
      unsafe++;
    }
  }

  fclose(input);

  printf("%i safe / %i unsafe\n", safe, unsafe);

  return 0;
}
