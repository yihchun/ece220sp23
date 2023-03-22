#include <stdio.h>
#include <string.h>
int *allocate_n_by_n_chess_board(unsigned int N) {
  int board[N][N];
  bzero(board, sizeof(board));
  return board;
}

void other_function() {
  int i, x[10000];
  for (i=0;i<10000;i++)
    x[i] = 100;
}

int main() {
  int x;
  int *p;
  int y;
  scanf("%d", &x);
  p = allocate_n_by_n_chess_board(x);
  other_function();
  printf("%d\n", *p);
  y = 3;
  printf("%d\n", y);
  return 0;
}
