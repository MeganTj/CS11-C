/*
 * Solves a Triangle Game that is played on a triangular board
 * with 15 equally spaced holes in it. A peg can move by jumping
 * over an adjacent peg into an empty space, horizontally and diagonally.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "triangle_routines.h"

#define NMOVES 36

int moves[NMOVES][3] =
{
  {0, 1, 3},
  {3, 1, 0},
  {1, 3, 6},
  {6, 3, 1},
  {3, 6, 10},
  {10, 6, 3},
  {0, 2, 5},
  {5, 2, 0},
  {2, 5, 9},
  {9, 5, 2},
  {5, 9, 14},
  {14, 9, 5},
  {2, 4, 7},
  {7, 4, 2},
  {4, 7, 11},
  {11, 7, 4},
  {5, 8, 12},
  {12, 8, 5},
  {1, 4, 8},
  {8, 4, 1},
  {4, 8, 13},
  {13, 8, 4},
  {3, 7, 12},
  {12, 7, 3},
  {3, 4, 5},
  {5, 4, 3},
  {6, 7, 8},
  {8, 7, 6},
  {7, 8, 9},
  {9, 8, 7},
  {10, 11, 12},
  {12, 11, 10},
  {11, 12, 13},
  {13, 12, 11},
  {12, 13, 14},
  {14, 13, 12}
};

#define BOARD_SIZE 15

/* Returns the number of pegs on the board. Takes in a board as an argument.
 * 
 */
int npegs(int board[])
{
  int i;
  int num_pegs = 0;
  for (i = 0; i < BOARD_SIZE; i++)
  {
    if (board[i] != 0)
    {
      num_pegs++;
    }
  }
  return num_pegs;
}

/* Returns 1 if the move is valid on this board, otherwise returns 0.
 * 
 * Takes in two arguments: a board, as well as a move, represented as an array
 * containing the initial position, the position being jumped over, and the
 * final position, in that order.
 */
int valid_move(int board[], int move[])
{
  if (board[move[0]] == 1 && board[move[1]] == 1 &&
      board[move[2]] == 0)
  {
    return 1;
  }
  return 0;
}

/* Makes this move on the board. 
 *
 * Takes in two arguments: a board, as well as a move, represented as an array
 * containing the initial position, the position being jumped over, and the
 * final position, in that order.
 */
void make_move(int board[], int move[])
{
  board[move[2]] = 1;
  board[move[1]] = 0;
  board[move[0]] = 0;
}

/* Unmakes this move on this board.
 * 
 * Takes in two arguments: a board, as well as a move, represented as an array
 * containing the initial position, the position being jumped over, and the
 * final position, in that order.
 */
void unmake_move(int board[], int move[])
{
  board[move[0]] = 1;
  board[move[1]] = 1;
  board[move[2]] = 0;
}

/*
 * Gets an initial board, represented as a 1-D array of integers.
 * A value of 0 in the array  means there is no peg at a location; a value of
 * 1 means that there is a peg. Does not permanently alter the board passed
 * in.
 *
 * Finds out if there are a set of moves which lead to having only a single
 * peg left on the board. Returns 1 if the board can be solved and 0 if it
 * cannot be solved.
 *
 * If at least one set of moves exist, print out the board positions that the 
 * moves go through, starting with a single peg, and ending with the user-
 * supplied board.
 */

int solve(int board[])
{
  int index = 0;
  int solvable;
  /* base case */
  if (npegs(board) == 1)
  {
    triangle_print(board);
    return 1;
  }
  /* recursive case */

  
  while (index < NMOVES)
  {
    if (valid_move(board, moves[index]) == 1)
    {
      make_move(board, moves[index]);
      solvable = solve(board);
      unmake_move(board, moves[index]);
      if (solvable == 1)
      {
        triangle_print(board);
        return 1;
      }
    }
    index++;
  }
  return 0; 
}

int main(void)
{
  int board[BOARD_SIZE];
  triangle_input(board); 
  if (solve(board) == 0)
  {
    fprintf(stderr, "The game is unsolvable.");
  }
  else
  {
    printf("Solved!");
  }
  return 0;
}
