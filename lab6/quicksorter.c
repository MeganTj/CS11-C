/* 
 * Takes in a list of numbers and prints them out in sorted order using
 * the quicksort algorithm and using a linked list to store the numbers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "memcheck.h"
#include "linked_list.h"

/* Takes in a linked list that stores numbers and sorts the numbers,
 * not modifying the linked list passed in.
 */
node * quicksort(node *list)
{
  node *copy;
  node *smaller;
  node *larger;
  node *small;
  node *large;
  node *sorted;
  node *half1;
  node *temp;
  node *n;
  int pivot;
  smaller = NULL;
  larger = NULL;
  if (list == NULL || list->next == NULL)
  {
    copy = copy_list(list);
    return copy;
  }
  else
  {
    copy = create_node(list->data, NULL);
    pivot = copy->data;
    for (n = list->next; n != NULL; n = n->next)
    {
      if (n->data < pivot)
      {
        temp = create_node(n->data, smaller);
        smaller = temp;
      }
      else
      {
        temp = create_node(n->data, larger);
        larger = temp;
      }
    }
    small = quicksort(smaller);
    large = quicksort(larger);
    half1 = append_lists(small, copy);
    sorted = append_lists(half1, large);
    free_list(smaller);
    free_list(larger);
    free_list(small);
    free_list(large);
    free_list(half1);
    free_list(copy);
  }
  is_sorted(sorted);
  return sorted;
  
}

/*
 * Prints a usage message. Takes in an argument, the name of the file.
 */
void usage(char name[])
{
  fprintf(stderr, "usage: %s [-q] number1 [number2 ...]", name);
  exit(1);
}

int main(int argc, char *argv[])
{
  int i;
  int num_int = 0;
  /* 0 refers to the output not suppressed. 1 refers to it
   * being suppressed.
   */
  int suppressed = 0;
  node *list;
  node *sorted_list;
  node *temp;
  list = NULL;
  for (i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-q") == 0)
    {
      suppressed = 1;
    }
    else 
    {
      temp = create_node(atoi(argv[i]), list);
      list = temp;
      num_int++;
    }
  }
  if (num_int == 0) 
  {
    usage(argv[0]);
  }
  sorted_list = quicksort(list);
  free_list(list);
  list = sorted_list;
  if (suppressed == 0)
  {
    print_list(list);
  }
  free_list(list);
  print_memory_leaks();
  return 0;
}

