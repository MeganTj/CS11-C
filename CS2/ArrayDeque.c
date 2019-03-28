/*
* An ArrayDeque that can add elements to the front or back end.
*/

#include<stdio.h> /*for printf and scanf*/
#include<stdlib.h> /*standard library*/
#include "memcheck.h"

#define DEFAULT_CAPACITY 10
#define GROW_FACTOR 2


typedef struct array_deque{
  int *arr;
  int capacity;
  int size;
} ArrayDeque;

ArrayDeque * ensureCapacity(ArrayDeque *deq) {
  ArrayDeque *newDeq;
  int *newArr;
  int *arr = deq->arr;
  int newCapacity;
  if (deq->capacity <= deq->size) {
    newCapacity = GROW_FACTOR * deq->capacity;
    newArr = (int *) realloc(arr, sizeof(int)*(newCapacity));
    if (newArr == NULL) {
       fprintf(stderr, "Out of memory!");
       exit(1);
    }
    newDeq = (ArrayDeque *) malloc(sizeof(ArrayDeque));
    if (newDeq == NULL) {
       fprintf(stderr, "Out of memory!");
       exit(1);
    }
    newDeq->arr = newArr;
    newDeq->capacity = newCapacity;
    newDeq->size = deq->size;
    /* free(arr); */
    free(deq);
    return newDeq;
  }
  return deq;
}

ArrayDeque * addFront(ArrayDeque *deq, int e) {
     int i;
     int *arr;
     int *end;
     int before;
     deq = (ArrayDeque *)ensureCapacity(deq);
     arr = deq->arr;
     end = arr + deq->size - 1;
     /*printf("%d\n", *end);*/
     for (i = deq->size - 1; i >= 0; i--) {
       before = *end;
       end++;
       *end = before;
       end -= 2; 
       /* arr[i+1] = arr[i]; */
     }
     *arr = e;
     deq->size++;
     for (i = 0; i < deq->capacity; i++) {
       printf("%d\n", arr[i]);
     }
     return deq;
}

ArrayDeque * addBack(ArrayDeque *deq, int e) {
  int *arr;
  deq = (ArrayDeque *) ensureCapacity(deq);
  arr = deq->arr + deq->size;
  *arr = e;
  deq->size++;
  return deq;
}

ArrayDeque * removeFront(ArrayDeque *deq) {
  int *curr = deq->arr;
  int *next = curr + 1;
  int val;
  int i;
  if (deq->size == 0) {
    return NULL;
  }
  for (i = 0; i < deq->size - 1; i++) {
    *curr = *next;
    curr++;
    next++;
  }
  deq.size--;
  return deq;
}

ArrayDeque * removeBack(ArrayDeque *deq) {
  int *curr = deq->arr;
  int *next = curr + 1;
  int val;
  int i;
  if (deq->size == 0) {
    return NULL;
  }
  for (i = 0; i < deq->size - 1; i++) {
    *curr = *next;
    curr++;
    next++;
  }
  deq.size--;
  return deq;
}

int main(void) {
  ArrayDeque *deq = (ArrayDeque *) malloc(sizeof(ArrayDeque));
    int *arr = (int *)calloc(DEFAULT_CAPACITY, sizeof(int));
    int size = 10;
    int i;
    if (deq == NULL) {
       fprintf(stderr, "Out of memory!");
       exit(1);
    }
    if (arr == NULL) {
       fprintf(stderr, "Out of memory!");
       exit(1);
    }
    for (i = 0; i < size; i++) {
       arr[i] = i + 1;
     }
    deq->arr = arr;
    deq->size = size;
    deq->capacity = DEFAULT_CAPACITY;
    deq = addFront(deq, 0);
    /* free(deq) before free(arr) or else get invalid error
     */
    free(deq);
    free(arr);
    print_memory_leaks();
    return 0;
}



