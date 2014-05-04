#include <stdio.h>

int main(int argc, char *argv[])
{
  enum Day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
  };
  enum Day day;
  printf("enum Day uninitialized has value of %d.\n", day);

  switch(day) {
  case MONDAY:
    printf("Monday is bad!\n");
    break;
  case FRIDAY:
    printf("Friday is better!\n");
    break;
  case SATURDAY:
  case SUNDAY:
    printf("Weekends is best!\n");
    break;
  default:
    printf("Mid days is neither good nor bad!\n");
  }
}
