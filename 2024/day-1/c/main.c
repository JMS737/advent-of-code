#include <stdio.h>
#include <stdlib.h>

#define MAX_LOCATIONS 5000
#define LOAD_ERROR -1

int getlocations(const char *filename, int *left, int *right, const unsigned int size) {
  FILE *locations = fopen(filename, "r");
  if (!locations) {
    fprintf(stderr, "File opening failed!\n");
    return LOAD_ERROR;
  }

  int locationLeft, locationRight;
  int line = 0;

  while (fscanf(locations, "%i   %i\n", &locationLeft, &locationRight) > 0) {
    if (line == size) {
      printf("exceeded maximum supported locations of %i\n", size);
      return LOAD_ERROR;
    }

    left[line] = locationLeft;
    right[line] = locationRight;
    line++;
  }

  // returns: the number of locations loaded from the file
  return line;
}

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

int processLocations(char *filename) {
  int left[MAX_LOCATIONS];
  int right[MAX_LOCATIONS];

  int nloc = getlocations(filename, left, right, MAX_LOCATIONS);
  if (nloc == LOAD_ERROR) {
    return LOAD_ERROR;
  }

  printf("loaded %i locations from file\n", nloc);

  qsort(left, nloc, sizeof(int), compareInt);
  qsort(right, nloc, sizeof(int), compareInt);

  int sum = 0;

  for (int i = 0; i < nloc; i++) {
    sum += abs(right[i] - left[i]);
    // printf("%i : L%i R%i Sum %i\n", i, left[i], right[i], sum);
  }
  printf("Total difference: %i\n", sum);

  int similarity = 0, iL = 0, iR = 0;

  for (iL = 0; iL < nloc; iL++) {
    while (iR < nloc && right[iR] <= left[iL]) {

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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage:\n    %s <input file name>\n", argv[0]);
    return 1;
  }

  if (processLocations(argv[1]) == LOAD_ERROR) {
    return EXIT_FAILURE;
  }
  return 0;
}
