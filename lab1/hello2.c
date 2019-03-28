/*
 * Asks the user to enter their first name and prints out a 
 * greeting.
 */

#include <stdio.h>

int main(void)
{
  char s[100];
  printf("Enter your name: ");
  scanf("%s", s);
  printf("hello, %s!\n", s);
  return 0;
}
