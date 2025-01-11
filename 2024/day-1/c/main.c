#include <stdio.h>
#include <stdlib.h>

int compareInt(const void *a, const void *b) {
  int int_a = *((int *)a);
  int int_b = *((int *)b);

  if (int_a == int_b) {
    return 0;
  } else if (int_a < int_b) {
    return -1;
  } else {
    return 1;
  }
}

int processLocations() {
  FILE *locations = fopen("../input.txt", "r");
  if (!locations) {
    fprintf(stderr, "File opening failed!\n");
    return EXIT_FAILURE;
  }

  int left[1000];
  int right[1000];
  int locationLeft;
  int locationRight;
  int line = 0;
  while (fscanf(locations, "%i   %i\n", &locationLeft, &locationRight) > 0) {
    if (line > 999) {
      printf("exceeded maximum supported locations of 1000");
      return EXIT_FAILURE;
    }
    left[line] = locationLeft;
    right[line] = locationRight;
    line++;
    //    printf("location found left='%i' right='%i'\n", locationLeft,
    //    locationRight);
  }

  qsort(left, 1000, sizeof(int), compareInt);
  qsort(right, 1000, sizeof(int), compareInt);

    FILE *out = fopen("sorted.txt", "w");

    for (int i = 0; i < 1000; i++){
        fprintf(out, "%i   %i\n", left[i], right[i]);
    }

  int sum = 0;

  for (int i = 0; i < 1000; i++) {
    sum += abs(right[i] - left[i]);
    // printf("%i : L%i R%i Sum %i\n", i, left[i], right[i], sum);
  }
  printf("Total difference: %i\n", sum);

  int similarity = 0, iL = 0, iR = 0;

  for (iL = 0; iL < 1000; iL++) {
    while (iR < 1000 && right[iR] <= left[iL]) {

      // printf("%i:%i : L%i R%i\n", iL, iR, left[iL], right[iR]);
      if (right[iR] == left[iL]) {
        // printf("adding match\n");
        similarity += right[iR];
      }
      iR++;
    }
  }

  printf("Simlarity: %i\n", similarity);
  return 0;
}

int main() {
  if (!processLocations()) {
    return EXIT_FAILURE;
  }
  return 0;
}
