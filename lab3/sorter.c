/*
 * Sorts integers using either the minimum element sort or the 
 * bubble sort algorithm. Takes in integers from the command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LENGTH 32

/*
 * Sorts an array of integers using the mimimum element sort algorithm. 
 * 
 * Takes in one argument: an array of integers.
 */
void min_sort(int num_elem, int arr[])
{
  int start;
  int smallest;
  int index;
  int temp;
  int i;
  start = 0;
  while (start < num_elem)
  {
    smallest = start;
    for (index = start; index < num_elem; index++)
    {      
      if (arr[index] < arr[smallest])
      {
        smallest = index;
      }
    }
    temp = arr[start];
    arr[start] = arr[smallest];
    arr[smallest] = temp;
    start++;
  }
  assert (start == num_elem);
  for (i = 1; i < num_elem; i++)
  {
    assert(arr[i] >= arr[i - 1]);
  }
}


/*
 * Sorts an array of integers using a bubble sort algorithm. 
 * 
 * Takes in one argument: an array of integers.
 */
void bubble_sort(int num_elem, int arr[])
{
  int num_swap;
  int index;
  int temp;
  int i;
  num_swap = -1;
  while (num_swap != 0)
  {
    num_swap = 0;
    for (index = 0; index < num_elem - 1; index++)
    {
      if (arr[index + 1] < arr[index])
      {
        temp = arr[index];
        arr[index] = arr[index + 1];
        arr[index + 1] = temp;
        num_swap += 1;
      }
    }
  }
  for (i = 1; i < num_elem; i++)
  {
    assert(arr[i] >= arr[i - 1]);
  }
}


/*
 * Prints a usage message.
 */
void usage(char name[])
{
  fprintf(stderr, "usage: %s [-b] [-q] number1 [number2 ...] (maximum \
    %d numbers)", name, MAX_LENGTH);
  exit(1);
}

int main(int argc, char *argv[])
{
  int i;
  /* 0 refers to minimum element. 1 refers to bubble sort. */
  int algo = 0;
  /* 0 refers to output not supressed. 1 means it is supressed. */
  int supressed = 0;
  int array[MAX_LENGTH];
  int num_int = 0;
  int index = 0;
  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-b") == 0)
    {
      algo = 1;
    }
    else if (strcmp(argv[i], "-q") == 0)
    {
      supressed = 1;
    }
    else if (num_int < 32)
    {
      array[num_int] = atoi(argv[i]);
      num_int++;
    }
    else
    {
      usage(argv[0]);
    }
  }
  if (num_int == 0) 
  {
    usage(argv[0]);
  }
  
  if (algo == 0)
  {
    min_sort(num_int, array);
  }
  else
  {
    bubble_sort(num_int, array);
  }
  if (supressed == 0)
  {
    for (index = 0; index < num_int; index++)
    {
      printf("%d\n", array[index]);
    }
  }
  return 0;
}
      

