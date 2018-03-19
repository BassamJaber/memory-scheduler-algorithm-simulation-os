#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *ptr;

struct node
{
  long processID;
  int processTime;
  int RemainingTime;
  int Priority;
  ptr next;
};

typedef ptr List;
typedef ptr Position;
typedef ptr Queue;
typedef ptr Process;

Process *array=NULL;                                   /*global Process Array*/
Queue readyQueue=NULL;

long numOfProcesses;
int burstTime;


Position createNode(long processID,int processTime,int RemainingTime,int Priority);                        /* create a Node */

List createList();                                 /* create a List */

void insertFirst(List L , Position P);             /* insert Node at the first */

void insertLast(List L,Position P);                /* insert node at the last */

Position deleteLast(List L);                       /*delete the Last node */

Position deleteFirst(List L);                      /* delete teh first Node*/

int isEmpty(List L);                               /* is the List Contain elements */

void Push(Queue Q,Position P);                      /*Push into the Queue */

Position Pop(Queue Q);                              /* Pop from the Queue */

int max(int x,int y);                              /*find the maximum between two numbers*/

int min(int x,int y);                              /*find the minimum between two numbers*/

/* Create a Random Process with Random Length and Priority*/
void createRandomProcess(long numOfProcesses , int minDuration , int maxDuration, int numOfPriorityLevel);

void printProcessInfo();               /*print information about processes*/

Position createEmptyNode();   /*Create an empty Node*/

void InsertListIntoReadyQueue();            /*Insert the Contetnt of Process Array into Ready queue*/

void printQueueContetnt(Queue Q);           /*Print the Queue contetnt*/

void firstComeFirstServedScheduling();

void shortestJobFirst();

void RoundRobinAlgorithm();

void MenuCase();

int menu();

void reload();

