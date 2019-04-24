/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include "lottery.h"
#include "general.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define 	UUID_LEN   40
#define 	MAX_TIP_LEN   17
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN + 1)

static FILE* fd;
static char separator;
static int drawingOfNumbers[TIP_SIZE];

bool init_lottery(const char *csv_file, char csv_separator)
{
  fd = fopen(csv_file, "r");
  if (fd == 0)
  {
    return false;
  }
  separator = csv_separator;
    for (int i = 0; i < TIP_SIZE; ++i)
    {
        drawingOfNumbers[i] = 0;
    }
  return true;
}

bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    if (tip_number < 0 || tip_number >= 44)
    {
      return false;
    }
    int count = 0;
    char line[MAX_LINE_LEN];
    while ( fgets(line, MAX_LINE_LEN, fd) != NULL)
    {
        if (count == tip_number)
        {
            count = 0;
            char str[2];
            str[0] = separator;
            str[1] = '\0';
            char* ptr = strtok(line, str);
            while(ptr != 0)
            {
                ptr = strtok(0, str);
                if (ptr == 0)
                {
                  break;
                }
                if (atoi(ptr) > 0 && atoi(ptr) <= 45)
                {
                    tip[count] = atoi(ptr);
                }
                count++;
            }
            rewind(fd);
            return true;
        }
        count++;
    }
  return false;
}

bool set_drawing(int drawing_numbers[TIP_SIZE])
{
  for (int i = 0; i < TIP_SIZE; i++) {

    if (drawing_numbers[i] <= 0 || drawing_numbers[i] > 45)
    {
      return false;
    }
    else
    {
      drawingOfNumbers[i] = drawing_numbers[i];
    }
  }
  return true;
}
bool empty(int drawing_numbers[]);
int get_tip_result(int tip_number)
{
  if (tip_number < 0 || tip_number >= 44)
  {
    return -2;
  }
  if (empty(drawingOfNumbers))
  {
    return -1;
  }
  int tip[TIP_SIZE];
  int counter = 0;
  get_tip(tip_number,tip);

  for (int i = 0; i < TIP_SIZE; i++)
  {
    for (int j = 0; j < TIP_SIZE; j++)
    {
      if (drawingOfNumbers[i] == tip[j])
      {
        counter++;
      }
    }
  }
  return counter;
}

int get_right_tips_count(int right_digits_count)
{
    if (right_digits_count < 0 || right_digits_count > TIP_SIZE || empty(drawingOfNumbers))
    {
      return -1;
    }
    int count = 0;
    int temp = 0;
    for (int i = 0; i < 44; ++i)
    {
        temp = get_tip_result(i);
        if (temp == right_digits_count)
        {
            count++;
        }
    }
  return count;
}


bool empty(int drawing_numbers[])
{
    for (int i = 0; i < TIP_SIZE; ++i)
    {
        if (drawing_numbers[i] != 0)
        {
          return false;
        }
    }
    return true;
}
