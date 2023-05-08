#include <event.h>
#include "event.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main() {

  Year *Patitin = createYear(-1);
  Stack *outdate = createStack(100);
  char buffer[10];
  int cmd;

  int year = -1, month = -1, day = -1, favorite = -1;
  char start[12], end[12], event[3000];

  // DailyNotification
  displayCurrentDateTask(Patitin);
  readTextFile(Patitin);
  // readOutDated(outdate);

  while (1) {

    // Clear Outdated
    cleanOutdatedData(Patitin, outdate);

    printf("-----------------------\n");
    printf("1  - Create task\n");
    printf("2  - Display all task\n");
    printf("3  - Display Outdated\n");
    printf("4  - Display Favorited\n");
    printf("5  - Delete task\n");
    printf("6  - Search\n");
    printf("7  - Edit\n");
    printf("10 - Clear\n");
    printf("99 - Exit\n");
    printf("Insert command :");

    fgets(buffer, 10, stdin);
    enterRemover(buffer);
    while (sscanf(buffer, "%d", &cmd) != 1) {
      printf("wrong command format please try again\n");
      printf("Inset command :");
      fgets(buffer, 10, stdin);
      enterRemover(buffer);
    }

    if (cmd == 1) {
      userInput(&year, &month, &day, start, end, event, &favorite, 1);
      insert(Patitin, year, month, day, start, end, event, favorite);
    }

    else if (cmd == 2) {
      int allTask = 0;
      displayAll(Patitin, 2, &allTask);
    }

    else if (cmd == 3) {
      displayOutdated(outdate);
    }

    else if (cmd == 4) {
      displayFavorite(Patitin);
    }

    else if (cmd == 5) {
      printf("Please input date to show all Lists in that day\n");
      userInput(&year, &month, &day, start, end, event, &favorite, 2);
      deleteEvent(Patitin, outdate, year, month, day);
    }

    else if (cmd == 6) {
      printf("Please insert date and name to search\n");
      printf("(leave \"--\" if don't want to search in that fields)\n");
      printf("*** for now you can only search by only one fields at the time "
             "***\n");
      userInput(&year, &month, &day, start, end, event, &favorite, 3);

      // searchByDate
      if (day != -1 && month != -1 && year != -1 && !strcmp(event, "--")) {
        displayByDate(Patitin, year, month, day);
      }
      // searchByDay
      else if (day != -1 && month == -1 && year == -1 && !strcmp(event, "--")) {
        displayByDay(Patitin, day);
      }
      // searchByMonth
      else if (day == -1 && month != -1 && year == -1 && !strcmp(event, "--")) {
        displayByMonth(Patitin, month);
      }
      // searchByYear
      else if (day == -1 && month == -1 && year != -1 && !strcmp(event, "--")) {
        displayByYear(Patitin, year);
      }
      // searchByName
      else if (day == -1 && month == -1 && year == -1 && strcmp(event, "--")) {
        displayByEvent(Patitin, event);
      }
    }

    else if (cmd == 7) {
      printf("Please input date to show all Lists in that day\n");
      userInput(&year, &month, &day, start, end, event, &favorite, 2);
      edit(Patitin, year, month, day);
    }

    else if (cmd == 10) {
      system("cls");
    }

    else if (cmd == 99)
      return 0;
    saveToText(Patitin);
    saveToOutdated(outdate);
  }

  return 0;
}
/*

1
02/03/05
23:00
23:30
Last Kuy
1
02/03/05
04:00
05:30
Last Kuy
1
02/03/05
12:00
12:30
Kuy2
1
02/03/05
22:00
23:59
Kuy3
1
03/04/05
12:00
13:00
Last Kuy
1
02/05/05
07:30
10:30
Last Kuy
1
02/05/06
19:44
23:56
Last Kuy
1
07/03/05
13:00
23:30
fak
1
12/03/06
13:00
23:30
fak2
2
*/