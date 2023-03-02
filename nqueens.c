#include <stdio.h>

/* Attempts to place n queens on the board so none can see each other
 * returns 0 if impossible, leaves board unchanged
 * returns 1 if successful, changes board to the solution
 */
int solve_nqueens(int *board, int N) {
  int i, j, k;
  /* make some progress towards the base case */
  for (i=0; i<N; i++) {
    for (j=0; j<N; j++) {
      if (board[i*N+j] == 1)
	break;
    }
    if (j == N) /* row i contains no queens */
      break;
  }
  if (i == N)
    return 1; /* base case: board contains N queens */
  /* i is the first row that contains no queens */
  for (j=0; j<N; j++) {
    /* if (!i && !j) continue; */
    /* check if [i][j] is a valid place for a queen */
    /* check to see if anyone else is on the same file */
    for (k=0; k<N; k++) {
      if (board[k*N+j] == 1)
	break;
    }
    if (k != N)
      continue;
    /* check the down-right diag (and up-left) */
    for (k=0;k<N;k++) {
      /* if there is a square on the kth row that corresponds to this
       * diagonal for the [i][j] location, it is at [k][j-i+k]
       */
      if ((j-i+k < 0) || (j-i+k >= N)) continue;
      //if ((j-i+k >= 0) && (j-i+k < N) && (board[k*N+(j-i+k)] == 1))
      if (board[k*N+(j-i+k)] == 1)
	break;
    }
    if (k != N)
      continue;
    
    /* check the down-left diag (and up-right) */
    for (k=0;k<N;k++) {
      /* if there is a square on the kth row that corresponds to this
       * diagonal for the [i][j] location, it is at [k][j+i-k]
       */
      if ((j+i-k < 0) || (j+i-k >= N)) continue;
      if (board[k*N+(j+i-k)] == 1)
	break;
    }
    if (k != N)
      continue;
    
    board[i*N+j] = 1;
    if (solve_nqueens(board, N))
      return 1;
    board[i*N+j] = 0;
  }
  return 0;
}

#define MY_N 8
int board[MY_N][MY_N];
int main() {
  int i, j;
  solve_nqueens(board, MY_N);
  for (i=0; i<MY_N; i++) {
    for (j=0; j<MY_N; j++)
      printf("%c", board[i][j] ? 'Q' : '-');
    printf("\n");
  }
  return 0;
}
