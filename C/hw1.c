// Libraries
#include <stdio.h>
#include <stdlib.h>

// Macros
#define WELCOME "Welcome to Assignment 1! This program will create programs for the job queue!"
#define START "****** PROGRAM START ******"
#define PRINT "\n****** BEGIN PRINTOUT ******"
#define FREE "\n\n\n****** BEGIN FREE ******"
#define SIZE 20
#define INITSTATE 0


// Structures
struct process{
  int pid;
  int state;
  int size;
  int start;
  char * description;
};


// Initialization
void printWelcome();
int getNumProcs();
int clearStdin();
void addProcs(int, struct process *);
void changeStates(int, struct process*);
int addInt(int *, char *);
void setStart(int, struct process *);
char * addString(char *);
void printProcs(struct process *);
char * getState(int);
void freeMemory(struct process *);


int main() {
  // Main method that does every function and grabs the processes for user input.
  int num;
  struct process * jobQueue = malloc(SIZE * sizeof(struct process));
  printf("\n");
  jobQueue[SIZE].pid = -1;
  printWelcome();
  num = getNumProcs();
  addProcs(num, jobQueue);
  printProcs(jobQueue);
  freeMemory(jobQueue);
  return 0;
}


// Prints the welcome statement
void printWelcome() {
  printf("%s\n\n", WELCOME);
  printf("%s\n\n", START);
}

// Grabs the number  of processes
int getNumProcs() {
  int num;
  char term;
  printf("Please enter a number of processes you would like to add: ");
  for (;;) {
    if(scanf("%d%c", &num, &term) != 2 || term != '\n') {
      printf("Please enter an integer! Try again: ");
      clearStdin();
    } else {
      break;
    }
  }
  return num;
}

// Clears standards in
int clearStdin() {
  int c = 0;
  while (('\n' != (c=fgetc(stdin))) && (c != EOF)) {
    if (c == EOF) break;
  }
  return 0;
}


// Adds the process size for the given prompt.
int addInt(int * num, char * prompt) {
  printf("%s", prompt);
  scanf("%d", num);
  return * num;
}

// Adds the description for the given prompt.
char * addString(char * prompt) {
  char * str;
  str = malloc(SIZE * sizeof(char *));
  str[SIZE-1] = '\0';
  printf("%s", prompt);
  scanf("%s", str);
  return str;
}

// Change all previous process states to 1
void changeStates(int num, struct process * jobQueue) {
  int i;
  for (i = 0; i < num; i++) {
    jobQueue[i].state = 1;
  }
}

// Calculate the start address for the process given.
void setStart(int num, struct process * jobQueue) {
  if (num = 0) {
    jobQueue[num].start = 0;
  } else {
    jobQueue[num].start = (jobQueue[num-1].start + jobQueue[num-1].size + 1);
  }
}

// Adds a new process with user input.
void addProcs(int loopNum, struct process * jobQueue) {
  int i;
  for (i = 0; i < loopNum; i++) {
    printf("\n***** New Process %d *****\n", i+1);
    jobQueue[i].pid = i+1;
    jobQueue[i].state = INITSTATE;
    changeStates(i, jobQueue);
    jobQueue[i].size = addInt(&jobQueue[i].size, "\n\tEnter process size: ");
    setStart(i, jobQueue);
    jobQueue[i].description = addString("\tEnter Description: ");
  }
  jobQueue[loopNum].pid = -1;
}

// Return start or ready based on state
char * getState(int state) {
  if (state = 0) {
    return "Start";
  } else if (state = 1) {
    return "Ready";
  } else {
    return "Error";
  }
}

// Printsa all the processes until the jobQueue[SIZE] in a pretty format.
void printProcs(struct process * jobQueue) {
  int num = -2;
  int count = 0;
  printf("%s\n\n", PRINT);
  while (num != -1 && count < SIZE) {
    num = jobQueue[count].pid;
    if (num != -1) {
      printf("\n\n****** Process Number %d Summary ******\n", count+1);
      printf("\n\tProcess ID: %d", jobQueue[count].pid);
      printf("\n\tProcess State: %s", getState(jobQueue[count].state));
      printf("\n\tProcess Size: %d", jobQueue[count].size);
      printf("\n\tProcess Description: %s", jobQueue[count].description);
    }
  count++;
  }
}

// Frees up memory allocations
void freeMemory(struct process * jobQueue) {
  int num = -2;
  int count = 0;
  printf("%s", FREE);
  while (num != -1 && count < SIZE) {
    num = jobQueue[count].pid;
    if (num != -1) {
      free(jobQueue[count].description);
    }
  count++;
  }
  free(jobQueue);
}
