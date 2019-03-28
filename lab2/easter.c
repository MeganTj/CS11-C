#include <stdio.h>
#include <stdlib.h>


/*
 * Calculates the day Easter occurs for a given year.
 *  
 * Takes in one argument, the year for which we want to find the date of Easter.
 * Returns the day of the month that Easter occurs. Return value is negative
 * if Easter is in March, positive if it is in April.
 */
int calculate_Easter_date(int year)
{
  /* Calculates the golden year. */
  int golden = year % 19 + 1;
  /* Calculates the century. */
  int century = year / 100 + 1;
  /* Calculates the skipped leap years. */
  int skipped = 3 * century / 4 - 12;
  /* Calculates the correction factor for the moon's orbit. */
  int correction = (8 * century + 5) / 25 - 5;
  /* Finds the day of the month that is a Sunday. */
  int day = 5 * year / 4 - skipped - 10;
  /* Calculates the "epact", or when a full moon occurs. */
  int epact = (11 * golden + 20 + correction - skipped) % 30;
  int day_march;
  if (year < 1582 || year > 39999)
  {
    return 0;
  }
  /* Increments the epact.  */
  if ((epact == 25 && golden > 11) || epact == 24)
  {
    epact++;
  }
  /* Calculates the day if it occurs in March. */
  day_march = 44 - epact;
  if (day_march < 21)
  {
    day_march += 30;
  }
  day_march = day_march + 7 - ((day + day_march) % 7);
  if (day_march > 31)
  {
    return day_march - 31;
  }
  else
  {
    return -day_march;
  }
}

/*
 * Takes in an input file, which contains years, each separated by a new line.
 * Prints the Easter date for each year to an output file. If the year is out
 * of range, prints an error message and continues the program.
 *
 * Returns 0.
 */
int main(void)
{
  int year;
  int date;
  int result;
  while(1)
  {
    result = scanf("%d", &year);
    if (result == EOF)
    {
      break;
    }      
    date = calculate_Easter_date(year);
    if (date == 0)
    {
      fprintf(stderr, "Input year is outside of range.");
    }
    else if (date < 0)
    {
      printf("%d - March %d\n", year, abs(date));
    }
    else
    {
      printf("%d - April %d\n", year, date);
    }
  }
  return 0;
}
