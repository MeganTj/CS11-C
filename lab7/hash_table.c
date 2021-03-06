/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"

const int TABLE_LENGTH = 128;


/*** Hash function. ***/

int hash(char *s)
{
  char *pos = s;
  int i;
  int value = 0;
  for (i = 0; i < sizeof(s); i += sizeof(char))
  {
    value += (int) *pos;
    pos++;
  }
  value %= TABLE_LENGTH;
  return value;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
  node *created;
  created = (node *)malloc(sizeof(node));
  if (created == NULL)
  {
    fprintf(stderr, "Fatal error: out of memory."
            "Terminating program.\n");
    exit(1);
  }
  created->key = key;
  created->value = value;
  created->next = NULL;
  return created;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
  node *pos;
  char *key;
  while (list != NULL)
  {
    pos = list;
    list = list->next;
    key = pos->key;
    free(key);
    free(pos);
  }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
  hash_table *table = (hash_table *)malloc(sizeof(hash_table));
  node **slot = (node **)calloc(TABLE_LENGTH, sizeof(node));
  if (table == NULL)
  {
    fprintf(stderr, "Fatal error: out of memory."
            "Terminating program.\n");
    exit(1);
  }
  if (slot == NULL)
  {
    fprintf(stderr, "Fatal error: out of memory."
            "Terminating program.\n");
    exit(1);
  }
  table->slot = slot;
  return table;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
  node **slot = ht->slot;
  node **loc = slot;
  int i;
  for (i = 0; i < TABLE_LENGTH; i++)
  {
    free_list(*loc);
    loc++;
  }
  free(slot);
  free(ht); 
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
  int val = hash(key);
  node **loc = ht->slot;
  node *n;
  int i;
  for (i = 0; i < val; i++)
  {
    loc++;
  }
  n = *loc;
  while (n != NULL && strcmp(key, n->key) != 0)
  {
    n = n->next;
  }
  if (n == NULL)
  {
    return 0;
  }
  else
  {
    return n->value;
  }
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
  int val = hash(key);
  node **loc = ht->slot;
  node *n;
  int i;
  for (i = 0; i < val; i++)
  {
    loc++;
  }
  n = *loc;
  while (n != NULL && strcmp(key, n->key) != 0)
  {
    n = n->next;
  }
  if (n == NULL)
  {
    n = *loc;
    *loc = create_node(key, value);
    (*loc)->next = n;
  }
  else
  {
    n->value = value;
    free(key);
  }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
  node **loc = ht->slot;
  node *n;
  int index;
  for (index = 0; index < TABLE_LENGTH; index++)
  {
    for (n = *loc; n != NULL; n = n->next)
    {
      printf("%s %d\n", n->key, n->value);
    }
    loc++;
  }
}


