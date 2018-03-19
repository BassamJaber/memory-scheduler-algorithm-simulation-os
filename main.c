#include "main.h"

int main(int argc , char *argv[])
{

  if (argc != 6) {
    fprintf(stderr, "usage:a.out #ofProcesses Minduration MaxDuration #ofPriorityLevel BurstTime\n");
    return -1;
  }
    numOfProcesses=atoi(argv[1]);
    int min,max;
    min=atoi(argv[2]);
    max=atoi(argv[3]);
    int plevel=atoi(argv[4]); 
    burstTime=atoi(argv[5]);
    createRandomProcess(numOfProcesses,min,max,plevel);

    InsertListIntoReadyQueue();
    MenuCase();
    //printQueueContetnt(readyQueue);
    //firstComeFirstServedScheduling();
    //shortestJobFirst();
    // RoundRobinAlgorithm();

    return 0;
}

void reload()
{
    Position P=readyQueue->next;
    while(P!=NULL)
    {
        P->RemainingTime=P->processTime;
        P=P->next;
    }
}

//Sub menu Cases For Printing The Tree
void MenuCase()
{
    int i;
    char ch;
    for( ; ; )
    {
        i=menu();
        switch(i)
        {
            case 1:firstComeFirstServedScheduling();
                   break;
            case 2:shortestJobFirst();
                   break;
            case 3:RoundRobinAlgorithm();
                   break;
            case 4: printf("Have a good Day\n");
                    exit(0);
                   break;
        }
        ch=getchar();
    }
}

//Menu Interface That Contain The Main Menu
int menu()
{
  char ch;
  do
  {

      printf("\t\t\t\t<*** Main Menu ***>\n\n\n");

      printf("1-First come First Served\n\n");

      printf("2-Shortest job first\n\n");

      printf("3-Round Robins RR\n\n");

      printf("4-Quit\n\n");
      printf("Enter Your Choice : ");
      ch=getchar();
  }while(!strchr("1234",ch));

    return (ch-48);
}

void RoundRobinAlgorithm()
{
  int waitingtime=0;
  int turnAroundTime=0;
  int count=0;
  Position P=readyQueue->next;
  int bt=burstTime;
  int i;
  for(i=0;i<numOfProcesses;)
  {
    while(P!=NULL)
    {
        if(P->RemainingTime==0)
        {
            P=P->next;
        }else {
                /**execute Process until the time Burst Ends or the Process Ends **/
                 while(P->RemainingTime!=0 && bt!=0 )
                 {
                     count++;
                     P->RemainingTime-=1;
                     bt--;
                 }
                 bt=burstTime;
                 /** if the Process ends we should Define two Parameters
                 **  first the Wait time for the Process
                 **  Second thing is the turn Around Time
                 **/
                 if(P->RemainingTime==0)
                 {
                     waitingtime+=count-P->processTime;
                     turnAroundTime+=count;
                     i++;   /** Process Done Incretemnt the Counter for the Process **/
                 }
              }
    }
    P=readyQueue->next;
  }
    double avg=(waitingtime/numOfProcesses);
    double avg1=(turnAroundTime/numOfProcesses);
    printf("Round Robin (RR) Scheduling\n\n\n");
    printf("Average Waiting time %0.3lf\n",avg);
    printf("Average Turn Around Time %0.3f\n\n\n\n",avg1);
    reload();

}

void shortestJobFirst()
{
    int waitingtime=0;
    int count=0;
    Position P=readyQueue->next;
    int min=999999;
    int i=0;
    int pid;
    /*We have a Certain Number Of Processes at the same time
     *We want to execute all the process shortest first
     */
    for(i=0;i<numOfProcesses;i++)
    {
       /*Loop to find the shortest Job to execute  */
       while(P!=NULL)
         {
           if(P->RemainingTime<min &&P->RemainingTime!=0)
           {
               min=P->RemainingTime;
               pid=P->processID;
           }
           P=P->next;
         }
         min=99999;
      P=readyQueue->next;
    /*find the shortest Process Again to execute it */
      while(P!=NULL && P->processID !=pid)
      {
          P=P->next;
      }
    waitingtime+=count;
    while(P->RemainingTime!=0)
      {
          P->RemainingTime=P->RemainingTime-1;
          count++;
      }
    }
    double avg=(waitingtime/numOfProcesses);
    printf("\n\n\nPreemtive Shortest-Job-First (SJR) Scheduling\n");
    printf("Average Waiting time %0.3lf\n\n\n",avg);
    reload();
}


void firstComeFirstServedScheduling()
{
  int count=0;
  int waitingTime=0;
  Position P=readyQueue->next;
  while(P!=NULL)
  {
      waitingTime+=count;
      while(P->RemainingTime!=0)
      {
          P->RemainingTime=P->RemainingTime-1;
          count++;
      }
      P=P->next;
  }
  double avg=(waitingTime/numOfProcesses);
  printf("\n\n\nFirst-Come, First-Served (FCFS) Scheduling \n\n");
  printf("Average Waiting time %0.3lf\n\n\n",avg);
  reload();
}
void InsertListIntoReadyQueue()
{
    readyQueue=(Queue)createList();
    Position P;
    int i;
    for(i=0;i<numOfProcesses;i++)
    {
        P=createEmptyNode();
        P->processID=array[i]->processID;
        P->processTime=array[i]->processTime;
        P->RemainingTime=array[i]->RemainingTime;
        P->Priority=array[i]->Priority;
        Push(readyQueue,P);
    }

}

void printQueueContetnt(Queue Q)
{
    Position P=Q->next;
    while(P!=NULL)
      {
          printf("Process ID %ld , Process Duration %d , Process Remaining time %d , Process Priority %d\n",P->processID,P->processTime,P->RemainingTime,P->Priority);
          P=P->next;
      }
}
void printProcessInfo()
{
    int i;
    for(i=0;i<numOfProcesses;i++)
      {
          printf("Process ID %ld , Process Duration %d , Process Remaining time %d , Process Priority %d\n",array[i]->processID,array[i]->processTime,array[i]->RemainingTime,array[i]->Priority);
      }
}

void createRandomProcess(long numOfProcesses , int minDuration , int maxDuration, int numOfPriorityLevel)
{
    array=(Process*)malloc(sizeof(Process)*numOfProcesses);
    if(array==NULL)
    {
        printf("Memory FULL\n");
        exit(0);
    }else{
            int i ;  /*Allocation for all Processes*/
            for(i=0;i<numOfProcesses;i++)
            {
                array[i]=(Process)malloc(sizeof(struct node));
            }

            int length=max(minDuration,maxDuration)-min(minDuration,maxDuration);
            int base=min(minDuration,maxDuration);

            for(i=0;i<numOfProcesses;i++)
            {
              array[i]->processID=i;
              array[i]->processTime=(base+rand()%length);
              array[i]->RemainingTime=array[i]->processTime;
              if(numOfPriorityLevel!=1)
                array[i]->Priority=(1+rand()%(numOfPriorityLevel-1));
              else
                array[i]->Priority=1;
            }

         }
}
int min(int x,int y)
{
   return ((x<y)?x:y);
}

int max(int x,int y)
{
    return ((x>y)?x:y);
}
Position createEmptyNode()
{
    Position P=(Position)malloc(sizeof(struct node));
    if(P==NULL)
    {
       printf("Memory Full !");
    }else{
           P->next=NULL;
        }
   return P;
}
Position createNode(long processID,int processTime,int RemainingTime,int Priority)
{
    Position P=(Position)malloc(sizeof(struct node));
    if(P==NULL)
    {
       printf("Memory Full !");
    }else{
           P->processID=processID;
           P->processTime=processTime;
           P->RemainingTime=RemainingTime;
           P->Priority=Priority;
           P->next=NULL;
        }
   return P;
}

List createList()
{
    List L=(List)malloc(sizeof(struct node));
    if(L==NULL)
    {
      printf("Memory Full");
      exit(0);
    }else{
           L->next=NULL;
         }
  return L;
}

void insertFirst(List L , Position P)
{
    if(L==NULL)
    {
        printf("List does Not Exist\n");
        exit(0);
    }else{
           P->next=L->next;
           L->next=P;
         }
}

void insertLast(List L,Position P)
{
    if(L==NULL)
    {
        printf("List does Not Exits\n");
        exit(0);
    }else {
             Position temp=L;
             while(temp->next!=NULL)
             {
                 temp=temp->next;
             }
             temp->next=P;
          }
}

Position deleteLast(List L)
{
    if(L==NULL)
    {
        printf("List Does not exitst\n");
        exit(0);
    }else if(isEmpty(L))
           {
               printf("List already Emptyn\n");
               return NULL;
           }else {
                    Position temp=L;
                    Position last=L;
                    int counter=0;
                    while(temp->next !=NULL)
                    {
                        temp=temp->next;
                        if(counter==0)
                           counter++;
                        if(counter==1)
                          last=last->next;
                    }
                    last->next=temp->next;
                    return temp;
                 }
}

Position deleteFirst(List L)
{
    if(L==NULL)
    {
        printf("List Does not exitst\n");
        exit(0);
    }else if(isEmpty(L))
           {
               printf("List already Emptyn\n");
               return NULL;
           }else {
                    Position temp=L->next;
                    L->next=temp->next;
                    return temp;
                 }
}

int isEmpty(List L)
{
    if(L==NULL)
    {
        printf("List Does not exist\n");
        exit(0);
    }else if(L->next==NULL)
            {
               return 1;
            }else {
                     return 0;
                  }
}

void Push(Queue Q,Position P)
{
   if(Q==NULL)
   {
       printf("Queue Does Not exitst\n");
       exit(0);
   }else {
            insertFirst(Q,P);
         }
}

Position Pop(Queue Q)
{
    if(Q==NULL)
    {
        printf("Queue Does Not exist\n");
        exit(0);
    }else {
             Position temp=deleteLast((List)Q);
             return temp;
          }
}
