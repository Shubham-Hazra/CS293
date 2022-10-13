#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

class BFSnode
{
public:
  int stnIndex;
  listOfObjects<TrainInfoPerStation *> *trains;
  listOfObjects<TrainInfoPerStation *> *trains_tail;

  BFSnode(int index)
  {
    stnIndex = index;
    trains = NULL;
    trains_tail = NULL;
  }
};

listOfObjects<TrainInfoPerStation *> *present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains);
listOfObjects<TrainInfoPerStation *> *BFS(listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int *visited, int dest_index, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> *trains_available, listOfObjects<TrainInfoPerStation *> *trains_available_tail);

listOfObjects<TrainInfoPerStation *> *present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains)
{
  while (trains != NULL)
  {
    if (trains->object->journeyCode == train->object->journeyCode)
    {
      return trains;
    }
    trains = trains->next;
  }
  return NULL;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int source_index;
  int dest_index;
  for (int i = 0; i < DICT_SIZE; i++)
  {
    if (stnNameToIndex.getKeyAtIndex(i) == srcStnName)
    {
      source_index = i;
      break;
    }
  }
  for (int i = 0; i < DICT_SIZE; i++)
  {
    if (stnNameToIndex.getKeyAtIndex(i) == destStnName)
    {
      dest_index = i;
      break;
    }
  }
  int *visited = new int[DICT_SIZE];
  for (int i = 0; i < DICT_SIZE; i++)
  {
    visited[i] = 0;
  }
  listOfObjects<TrainInfoPerStation *> *trains_available = NULL;
  listOfObjects<TrainInfoPerStation *> *trains_available_tail = NULL;
  BFSnode *new_node = new BFSnode(source_index);
  listOfObjects<BFSnode *> *q = new listOfObjects<BFSnode *>(new_node);
  listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[source_index].toStations;
  while (currStnConnInfo != NULL)
  {
    listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
    while (trains != NULL)
    {
      if (q->object->trains == NULL)
      {
        q->object->trains = new listOfObjects<TrainInfoPerStation *>(trains->object);
        q->object->trains_tail = q->object->trains;
      }
      else
      {
        q->object->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(trains->object);
        q->object->trains_tail = q->object->trains_tail->next;
      }
      trains = trains->next;
    }
    currStnConnInfo = currStnConnInfo->next;
  }
  listOfObjects<BFSnode *> *tail;
  tail = q;
  trains_available = BFS(q, tail, visited, dest_index, adjacency, trains_available, trains_available_tail);
  if (trains_available == NULL)
  {
    cout << "No direct journies available" << endl;
  }
  else
  {
    cout << "Journey Available" << endl;
    printStationInfo(trains_available);
  }
  return;
}

listOfObjects<TrainInfoPerStation *> *BFS(listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int *visited, int dest_index, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> *trains_available, listOfObjects<TrainInfoPerStation *> *trains_available_tail)
{
  if (q != NULL)
  {
    int index = q->object->stnIndex;
    visited[index] = 1;
    listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[index].toStations;
    while (currStnConnInfo != NULL)
    {
      if (visited[currStnConnInfo->object->adjacentStnIndex] == 0)
      {
        if (currStnConnInfo->object->adjacentStnIndex == dest_index)
        {
          listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
          while (trains != NULL)
          {
            if (trains_available == NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = present(trains, q->object->trains);
              if (train != NULL)
              {
                trains_available = new listOfObjects<TrainInfoPerStation *>(train->object);
                trains_available_tail = trains_available;
              }
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *train = present(trains, q->object->trains);
              if (train != NULL)
              {
                trains_available_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                trains_available_tail = trains_available_tail->next;
              }
            }
            trains = trains->next;
          }
        }
        else
        {
          BFSnode *new_node = new BFSnode(currStnConnInfo->object->adjacentStnIndex);
          listOfObjects<BFSnode *> *node = new listOfObjects<BFSnode *>(new_node);
          listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
          while (trains != NULL)
          {
            if (node->object->trains == NULL)
            {
              listOfObjects<TrainInfoPerStation *> *train = present(trains, q->object->trains);
              if (train != NULL)
              {
                node->object->trains = new listOfObjects<TrainInfoPerStation *>(train->object);
                node->object->trains_tail = node->object->trains;
              }
            }
            else
            {
              listOfObjects<TrainInfoPerStation *> *train = present(trains, q->object->trains);
              if (train != NULL)
              {
                node->object->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                node->object->trains_tail = node->object->trains_tail->next;
              }
            }
            trains = trains->next;
          }
          tail->next = node;
          tail = node;
        }
      }
      currStnConnInfo = currStnConnInfo->next;
    }
    q = q->next;
    trains_available = BFS(q, tail, visited, dest_index, adjacency, trains_available, trains_available_tail);
  }
  return trains_available;
}