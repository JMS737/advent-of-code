#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int is_odd_length(uint id) {
  int len = 1;
  while (id >= 10) {
    len++;
    id /= 10;
  }

  return len % 2 == 1;
}

int is_odd_length_str(const char *id) { return strlen(id) % 2 == 1; }

int is_repeated_twice(const char *id) {
  int len = strlen(id);
  int half = len / 2;

  char a[6], b[6];

  strncpy(a, id, half);
  a[half] = '\0';

  strncpy(b, id + half, half);
  b[half] = '\0';

  if (strcmp(a, b) == 0) {
    return 1;
  }

  return 0;
}

int is_repeated_n_times(const char *id, int n) {
  char buf[n][6];
  int len, n_size;

  len = strlen(id);
  // ignore those which do not sub divide into n cleanly
  if (len % n != 0) {
    return 0;
  }

  // printf("checking %s repeats %d times\n", id, n);
  n_size = len / n;

  // load all substrings into the buffer.
  for (int i = 0; i < n; i++) {
    strncpy(buf[i], id + (i * n_size), n_size);
    buf[i][n_size] = '\0';
  }

  // check all substrings match
  for (int i = 1; i < n; i++) {
    if (strcmp(buf[i - 1], buf[i]) != 0) {
      return 0;
    }
  }

  // all substrings match if we got here.
  return 1;
}

int is_repeated_any_number_of_times(const char *id) {
  int len = strlen(id);

  for (int i = 2; i <= len; i++) {
    if (is_repeated_n_times(id, i)) {
      return 1;
    }
  }

  return 0;
}

int is_invalid(ulong id) {
  // Max int will be 10 characters, plus one for the terminating string
  // character
  char id_str[11];
  snprintf(id_str, sizeof(id_str), "%lu", id);

  // if (is_odd_length_str(id_str)) {
  //   return 0;
  // }

  if (is_repeated_any_number_of_times(id_str)) {
    return 1;
  }

  return 0;
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage:\n    %s <input file path>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "Failed to open file.");
    return 1;
  }

  ulong sum;
  ulong a, b;
  while (fscanf(file, "%lu-%lu,", &a, &b) > 0) {
    printf("\na=%lu - b=%lu\n", a, b);
    for (ulong i = a; i <= b; i++) {
      if (is_invalid(i)) {
        sum += i;
        // printf("  Invalid: %lu\n", i);
      } else {
        // printf("    Valid: %lu\n", i);
      }
    }
  }

  printf("\nTotal: %lu\n", sum);
  return 0;
}
