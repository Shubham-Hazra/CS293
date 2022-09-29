#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <cstdlib>
#include "math.h"



void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  listOfObjects<TrainInfoPerStation *> *end = stnInfoList;
  while(end->next!=NULL)
  {
    end = end->next;
  }
  quicksort(stnInfoList,end);
}

void quicksort(listOfObjects<TrainInfoPerStation *> *a , listOfObjects<TrainInfoPerStation *> *b)
{
  if(a == b)
  {
    return;
  }
  listOfObjects<TrainInfoPerStation *>* pivot = partition(a,b);
  quicksort(a,pivot->prev);
  quicksort(pivot->next,b);
}


listOfObjects<TrainInfoPerStation *>* partition(listOfObjects<TrainInfoPerStation *> *a , listOfObjects<TrainInfoPerStation *> *b)
{
  listOfObjects<TrainInfoPerStation *>* pivot = pivot_chooser(a ,b);
  listOfObjects<TrainInfoPerStation *> *start = a;
  listOfObjects<TrainInfoPerStation *> *end = b->prev;
  swap(pivot,b);
  while(start!=end)
  {
    
  }
}

void swap(listOfObjects<TrainInfoPerStation *> *a , listOfObjects<TrainInfoPerStation *> *b)
{
  a->prev->next = b;
  b->prev->next = a;
  listOfObjects<TrainInfoPerStation *> *temp = b->next;
  b->next = a->next;
  a->next = temp;
}

listOfObjects<TrainInfoPerStation *>* pivot_chooser(listOfObjects<TrainInfoPerStation *> *a , listOfObjects<TrainInfoPerStation *> *b)
{
  srand(time(0));
  int len = 0;
  listOfObjects<TrainInfoPerStation *>* ptr = a;
  while(ptr!=b->next)
  {
    len++;
    ptr = ptr->next;
  }
  int pivot_steps =  rand()%len;

  listOfObjects<TrainInfoPerStation *>* pivot = a;
  for(int i=0;i<pivot_steps;i++)
  {
    pivot = pivot->next;
  }
  return pivot;
}