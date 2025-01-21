#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_board(const char *filename, int size, char board[][size]) {
  FILE *input = fopen(filename, "r");

  if (input == NULL) {
    return 1;
  }

  int b_size = size + 2;
  char line[b_size]; // an area to write data including the newline and
                     // termination characters
  int row = 0;

  while (fgets(line, b_size, input)) {
    stpncpy(board[row], line, size);
    // printf("read row %d end char '%c' board '%c'\n", row, line[size - 1],
    //        board[row][size - 1]);
    row++;
  }

  fclose(input);
  return 0;
}

void print_board(int size, char board[][size]) {
  int i, j;
  for (j = 0; j < size; j++) {
    for (i = 0; i < size; i++) {
      printf("%c", board[j][i]);
    }
    printf("\n");
  }
}

struct board_pos {
  int j;
  int i;
};

struct direction {
  int j;
  int i;
};

struct board_pos add(struct board_pos pos, const struct direction dir) {
  pos.j += dir.j;
  pos.i += dir.i;
  return pos;
}

int exists_word(int size, const char board[][size], const char *word,
                const int i_char, struct board_pos pos,
                const struct direction dir) {
  // if we reach the end of the search word, we must have found the full word!
  if (word[i_char] == '\0') {
    return 1;
  }

  if (pos.j < 0 || pos.j >= size || pos.i < 0 || pos.i >= size) {
    // out of bounds
    return 0;
  }

  // if the character matches the expected one, recursively check the next
  // character and position
  if (board[pos.j][pos.i] == word[i_char]) {
    return exists_word(size, board, word, i_char + 1, add(pos, dir), dir);
  }

  return 0;
}

int scan_directions(const struct board_pos pos, const char *word,
                    const int size, const char board[][size]) {
  int count = 0;
  struct direction dir;

  for (dir.j = -1; dir.j < 2; dir.j++) {
    for (dir.i = -1; dir.i < 2; dir.i++) {
      if (dir.j == 0 && dir.i == 0) {
        continue;
      }
      count += exists_word(size, board, word, 1, add(pos, dir), dir);
    }
  }

  return count;
}

int find_occurrences(const char *word, const int size,
                     const char board[][size]) {
  int count = 0;
  struct board_pos pos;

  for (pos.j = 0; pos.j < size; pos.j++) {
    for (pos.i = 0; pos.i < size; pos.i++) {
      if (board[pos.j][pos.i] == word[0]) {
        count += scan_directions(pos, word, size, board);
      }
    }
  }

  return count;
}

const static struct direction TOP_LEFT = {-1, -1};
const static struct direction TOP_RIGHT = {-1, 1};
const static struct direction BOTTOM_LEFT = {1, -1};
const static struct direction BOTTOM_RIGHT = {1, 1};

char c_at(struct board_pos pos, int size, const char board[][size]) {
  return board[pos.j][pos.i];
}

int is_valid(struct board_pos pos_a, struct board_pos pos_b, int size, const char board[][size]) {
  char a = c_at(pos_a, size, board);
  char b = c_at(pos_b, size, board);
  return (a == 'M' && b == 'S') || (a == 'S' && b == 'M');
}

int exists_cross(struct board_pos *pos, int size, const char board[][size]) {
  if (is_valid(add(*pos, TOP_LEFT), add(*pos, BOTTOM_RIGHT), size, board)
    && is_valid(add(*pos, TOP_RIGHT), add(*pos, BOTTOM_LEFT), size, board)) {
    return 1;
  }
  return 0;
}

int find_occurrences_part_2(int size, const char board[][size]) {
  int count = 0;

  struct board_pos pos;

  for (pos.j = 1; pos.j < size - 1; pos.j++) {
    for (pos.i = 1; pos.i < size - 1; pos.i++) {
      if (board[pos.j][pos.i] == 'A') {
        // TODO: implement search for M and S diagonally
        count += exists_cross(&pos, size, board);
      }
    }
  }
  return count;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage:\n   %s <size> <input file path>\n", argv[0]);
    return EXIT_FAILURE;
  }

  int size = atoi(argv[1]);

  char board[size][size];
  const char search_word[] = "XMAS";

  load_board(argv[2], size, board);
  // print_board(size, board);

  struct board_pos start = {1, 0};
  struct direction dir = {1, 0};

  int count = find_occurrences(search_word, size, board);
  printf("found %d occurrences of '%s'\n", count, search_word);

  count = find_occurrences_part_2(size, board);
  printf("found %d occurrences of XMAS Crosses'\n", count);
  // int found = exists_word(size, board, search_word, 0, start, dir);

  // if (found) {
  //   printf("'%s' was found at %d,%d in direction %d,%d\n", search_word,
  //          start.i, start.j, dir.i, dir.j);
  // } else {
  //   printf("not found\n");
  // }

  return EXIT_SUCCESS;
}
