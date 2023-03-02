#include <stdio.h>

/* given an (N*N)*(N*N) array
 * each location contains 0 if empty, or 1..N*N if populated
 * return 1 with a solved board
 * return 0 if unsolvable (and leave board unchanged)
 * PRE: the sudoku rules are followed (rows, columns, subsquares
 *      don't have repeated values other than 0)
 */
int sudoku_solver(int *board, int N) {
  int i, j, k, l, m, n, o, p;
  for (i=0; i<N*N; i++) {
    for (j=0; j<N*N; j++) {
      if (board[i*N*N+j] == 0)
	break;
    }
    if (j != N*N) break;
  }
  if (i == N*N) return 1;
  /* [i][j] is unpopulated, make progress by sticking something
   * in [i][j]
   */
  for (k=1; k<=N*N; k++) {
    /* can we place k here? */
    /* row */
    for (l=0; l<N*N; l++)
      if (board[i*N*N+l] == k)
	break;
    if (l != N*N) continue;
    
    /* col */
    for (l=0; l<N*N; l++)
      if (board[l*N*N+j] == k)
	break;
    if (l != N*N) continue;
    
    /* nxn square */
    for (l=i-i%N; l<i-i%N+N; l++) {
      for (m=j-j%N; m<j-j%N+N; m++) {
	if (board[l*N*N+m] == k)
	  break;
      }
      if (m != j-j%N+N) break;
    }
    if (l != i-i%N+N) continue;
    
    board[i*N*N+j] = k;
    if (sudoku_solver(board, N))
      return 1;
    board[i*N*N+j] = 0;
  }
  return 0;
}

int board[9][9];
int main() {
  int i,j ;
  sudoku_solver(board, 3);
  for (i=0; i<9; i++) {
    for (j=0; j<9; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
  return 0;
}
