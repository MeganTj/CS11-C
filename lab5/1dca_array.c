/*
 * Creates a one-dimensional cellular automaton. Consists of a collection of 
 * cells that can hold data values all arranged in a line. Each cell's value
 * at the next time interval depends on the current value as well as the 
 * value of its two immediate neighbors. Each cell can either be full or 
 * empty, represented by 1 and 0 respectively.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memcheck.h"

/* Prints out a cellular automaton. Takes in two arguments: the length of 
 * the CA and the CA itself, represented as an array. Represents 0's as 
 * "." and 1's as "*".
 */
void ca_print(int size, int arr[])
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (arr[i] == 1)
    {
      printf("*");
    }
    else
    {
      printf(".");
    }
  }
  printf("\n");
}


/* Updates the CA based on the following update rule: if the current cell is
 * empty and one of the two adjacent cells is full (but not both), set the 
 * current cell to be full; otherwise, set the current cell to be empty.
 */
void update(int rep, int size, int arr[])
{
  int *prev_gen;
  int *next_gen;
  int index;
  int i;
  prev_gen = arr;
  next_gen = (int *)calloc(size, sizeof(int));
  if (prev_gen == NULL)
  {
    fprintf(stderr, "Error! Memory allocation failed!\n");
    exit(1);
  }
  if (next_gen == NULL)
  {
    fprintf(stderr, "Error! Memory allocation failed!\n");
    exit(1);
  }
  ca_print(size, prev_gen);
  for (index = 0; index < rep; index++)
  {
    for (i = 1; i < size - 1; i++)
    {
      if (prev_gen[i] == 0 &&
          prev_gen[i - 1] + prev_gen[i + 1] == 1)
      {
        next_gen[i] = 1;
      }
      else
      {
        next_gen[i] = 0;
      }
    }
    ca_print(size, next_gen);
    /* Copies the contents of next_gen to prev_gen. */
    for (i = 0; i < size; i++)
    {
      prev_gen[i] = next_gen[i];
    }
  }
  free(prev_gen);
  free(next_gen);
}

int main(int argc, char *argv[])
{
  int num_cell;
  int num_gen;
  int *arr;
  int i;
  srand(time(0));
  if (argc == 1)
  {
    fprintf(stderr, "Two command-line arguments required.\n");
    exit(1);
  }
  num_cell = atoi(argv[1]);
  num_gen = atoi(argv[2]);
  arr = (int *)calloc(num_cell, sizeof(int));
  for (i = 0; i < num_cell; i++)
  {
    arr[i] = rand() % 2;
  }
  update(num_gen, num_cell, arr);
  print_memory_leaks();
  return 0;
}
