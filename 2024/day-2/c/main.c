#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DAMPENER_ENABLED 1
#define LINE_SIZE 100

// Requirements
//   A level transition is valid if the following is true:
//     - ALL transitions are increasing, or ALL are decreasing
//     - The transition delta must be 1 <= delta <= 3
int evaluate_transition(int a, int b, int *direction) {
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
  int next, prev;

  // store the direction outside so it can persist between all checks
  int direction = 0;

  // strtok modifies the string, so make a mutable copy
  char line_copy[LINE_SIZE];
  strcpy(line_copy, line);

  char *token = strtok(line_copy, " ");

  if (token != NULL) {
    prev = atoi(token);
    token = strtok(NULL, " ");
  }

  while (token != NULL) {
    next = atoi(token);

    if (!evaluate_transition(prev, next, &direction)) {
      return 0;
    }
    prev = next;
    token = strtok(NULL, " ");
  }

  return 1;
}

// Copies all tokens from one string to another
// excluding the token at the given index 'skip'
const char *remove_level(char *new_line, const char *line, int skip) {
  int i = 0;
  int n_head = 0;
  int iToken = 0;

  while (i < LINE_SIZE) {

    if (iToken != skip || line[i] == '\n') {
      new_line[n_head] = line[i];
      n_head++;
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

  // if skip was the last token in the string it will leave a trailing space
  // which breaks the evaluate method, so shift the new line over
  if (new_line[n_head - 2] == ' ') {
    new_line[n_head - 2] = '\n';
    new_line[n_head -1] = 0;
  }

  // fill the rest of the string will null values as memory location may
  // or may not be reused
  while (n_head < LINE_SIZE) {
    new_line[n_head] = 0;
    n_head++;
  }

  return new_line;
}

// Test all combinations of the string with one of the levels removed
// to see if one of them is valid
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
