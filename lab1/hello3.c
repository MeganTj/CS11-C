/*
 * Asks the user to enter their first name. A greeting is printed
 * to stdout a random number of times. There are two possible 
 * greetings, depending on whether the random number is even or odd.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
  srand(time(0));
  int i;
  int n;
  char s[100];

  n = rand() % 10;
  printf("Enter your name: ");
  scanf("%s", s);

  if (n % 2 == 0)
  {
    for (i = 0; i < n; i++)
    {
      printf("%d: hello, %s!\n", n, s);
    }  
  }
  else
  {
    for (i = 0; i < n; i++)
    {
      printf("%d: hi there, %s!\n", n, s);
    }    
  }
  return 0;
}
