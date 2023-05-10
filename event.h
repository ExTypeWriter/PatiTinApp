#ifndef EVENT_H
#define EVENT_H
typedef struct event {
  char *event;
  char startTime[12];
  char endTime[12];
  int favorite;
  struct event *next;
} Event;

typedef struct day {
  int day;
  struct day *next;
  struct event *event;
} Day;

typedef struct month {
  int month;
  struct day *day;
  struct month *next;
} Month;

typedef struct year {
  int year;
  struct month *month;
  struct year *next;
} Year;

typedef struct stack {
  int top;
  int size;
  Year *arr[100];
} Stack;

Stack *createStack(int size);
void push(Stack *stack, Year *curYear);
void pop(Stack *stack);
Year *peek(Stack *stack);

void enterRemover(char *str);
void trim(char *str);

int isOutdatedData(int year, int month, int day, char *eventTime);
int findDateBlank(char *date, int *day, int *month, int *year);
int findTimeBlank(char *time);
int findFavBlank(char *buffer, int *fav);

int validateDate(char *date);
int validateDateNum(int year, int month, int day);
int validateTime(char *time);

Event *createEvent(char *str, char start[], char end[], int favorite);
Day *createDay(int day);
Month *createMonth(int month);
Year *createYear(int year);

Year *searchByYear(Year *curYear, Year **prev, int year);
Year *searchByYearFromOutdated(Stack *outdated, int year);
Month *searchByMonth(Month *curMonth, Month **prev, int month);
Day *searchByDay(Day *curDay, Day **prev, int day);
Day *searchByDate(Year *headYear, int year, int month, int day);
Day *searchByDateFromOutdated(Stack *outdated, int year, int month, int day);

void displayCurrentTime();
void displayFavorite(Year *headYear);
void displayOriginalDate(Year *headYear, Event *current);
void displayByEvent(Year *headYear, char eventName[]);
void displayDayTask(Day *curDay);
void displayByDate(Year *headYear, int year, int month, int day);
void displayByDay(Year *headYear, int day);
void displayCurrentDateTask(Year *headYear);
void displayByMonth(Year *headYear, int month);
void displayByYear(Year *headYear, int year);
void displayOutdated(Stack *outdated);
void displayAll(Year *headYear, int opr, int *allTask);

void deleteFirstEvent(Year *headYear, int number, int year, int month, int day);
void deleteEvent(Year *headYear, Stack *outdated, int year, int month, int day);

void insert(Year *headYear, int year, int month, int day, char start[],
            char end[], char event[], int favorite);

Event *getEvent(Year *headYear, Event *current);

void userInput(int *year, int *month, int *day, char *start, char *end,
               char *event, int *favorite, int type);

void edit(Year *headYear, int year, int month, int day);

void cleanOutdatedData(Year *headYear, Stack *stack);

void saveToText(Year *headYear);
void readTextFile(Year *headYear);

void outDatedList(Year *headYear, int year);
void saveToOutdated(Stack *outdated);
void readOutDated(Stack *stack);

#endif

