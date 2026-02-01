#include <stdio.h>

static int cur = 50;
static int prev;
static int zeroCount = 0;

void apply(char dir, int count, int isIntermediate) {
  int prev = cur;

  // Apply one rotation at a time for simplicity.
  while (count > 100) {
    apply(dir, 100, 1);
    count -= 100;
  }

  // Apply the count to the current position
  if (dir == 'R') {
    cur += count;
  } else {
    cur -= count;
  }

  // Means we've Passed zero (and are not on zero).
  // We don't want to count this if we were previous on zero.
  if ((cur < 0 || cur > 100) && (prev != 0)) {
    zeroCount++;
  }

  // Normalize the count back to the 0-99 range.
  if (cur < 0) {
    cur += 100;
  } else if (cur > 99) {
    cur -= 100;
  }

  // If the position is currently on zero, add one to the count.
  if (cur == 0) {
    zeroCount++;
  }
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    printf("Useage:\n    %s <input file name>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");

  if (!file) {
    fprintf(stderr, "Failed to open file\n");
    return 1;
  }

  char dir;
  int count;

  while (fscanf(file, "%c%i\n", &dir, &count) > 0) {
    prev = cur;
    apply(dir, count, 0);

    printf("%c%i : %i > %i; %i zeros\n", dir, count, prev, cur, zeroCount);
  }

  fclose(file);

  return 0;
}
