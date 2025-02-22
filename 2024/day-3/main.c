#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 10000

int main(int argc, char *argv[]) {
  char *filename;

  if (argc != 2) {
    printf("Usage:\n    %s <input file path>\n", argv[0]);
    return 1;
  }

  filename = argv[1];

  FILE *input = fopen(filename, "r");

  if (input == NULL) {
    printf("could not open file '%s'\n", filename);
    return 1;
  }

  int sum = 0;
  int a, b;
  int len;
  int enabled = 1;

  char line[LINE_SIZE];
  char line_match[13];
  char *line_start; // keep track of our current position in the line buffer
  char pattern[] = "(mul\\([0-9]+,[0-9]+\\)|do(n't){0,1}\\(\\))";

  regex_t regex;
  regmatch_t matches[1]; // stores the single match (if any) returned by regexec

  regcomp(&regex, pattern, REG_EXTENDED);

  while (fgets(line, LINE_SIZE, input) != NULL) {
    // printf("read line %s\n", line);
    line_start = line;

    while (!regexec(&regex, line_start, 1, matches, REG_EXTENDED)) {
      line_start += matches[0].rm_so;
      len = matches[0].rm_eo - matches[0].rm_so;

      strncpy(line_match, line_start, len);
      // set the termination charater to prevent any existing data in the buffer
      // from being considered
      // (not actually necessary for this use case but good to know)
      line_match[len] = '\0';
      // printf("found match '%s'\n", line_match);
      line_start += len;

      if (line_match[2] == 'n') {
        enabled = 0;
      } else if (line_match[2] == '(') {
        enabled = 1;
      } else {
        if (enabled) {
          sscanf(line_match, "mul(%d,%d)", &a, &b);
          // printf("adding %d * %d = %d\n", a, b, a * b);
          sum += a * b;
        } else {
          // printf("skipping\n");
        }
      }
    }
  }

  fclose(input);

  printf("the sum of valid operations is %i\n", sum);

  return 1;
}
