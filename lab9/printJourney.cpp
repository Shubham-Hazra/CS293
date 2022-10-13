#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// Class made to use as the nodes in a queue used for BFS
// Contains information about the index of the station and the trains leaving from the station which also departed from the source station
// Has a doubly linked list of TrainInfoPerStation
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

// Function Prototypes
listOfObjects<TrainInfoPerStation *> *present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains);
listOfObjects<TrainInfoPerStation *> *BFS(listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int source_index, int dest_index, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> *trains_available, listOfObjects<TrainInfoPerStation *> *trains_available_tail);

// Function to search for a train in a given list of trains(Using journey codes)
// If found returns the TrainInfoPerStation object from the list else returns NULL
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

// Main function in which BFS is called
// Lists all the direct journeys from source to destination
void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  int source_index;
  int dest_index;
  for (int i = 0; i < DICT_SIZE; i++) // To get the index of the source station
  {
    if (stnNameToIndex.getKeyAtIndex(i) == srcStnName)
    {
      source_index = i;
      break;
    }
  }
  for (int i = 0; i < DICT_SIZE; i++) // To get the index of the destination
  {
    if (stnNameToIndex.getKeyAtIndex(i) == destStnName)
    {
      dest_index = i;
      break;
    }
  }
  listOfObjects<TrainInfoPerStation *> *trains_available = NULL; // The linked list which will contain all the feasible journies
  listOfObjects<TrainInfoPerStation *> *trains_available_tail = NULL;
  BFSnode *new_node = new BFSnode(source_index);
  listOfObjects<BFSnode *> *q = new listOfObjects<BFSnode *>(new_node); // The first element of the queue(The source station)
  listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[source_index].toStations;
  listOfObjects<TrainInfoPerStation *> *source_trains = stationInfo[source_index];
  while (currStnConnInfo != NULL) // Population the BFSnode of the source station with trains leaving from the source station
  {
    listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
    while (trains != NULL)
    {
      listOfObjects<TrainInfoPerStation *> *train = present(trains, source_trains);
      if (q->object->trains == NULL)
      {
        q->object->trains = new listOfObjects<TrainInfoPerStation *>(train->object);
        q->object->trains_tail = q->object->trains;
      }
      else
      {
        q->object->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
        q->object->trains_tail = q->object->trains_tail->next;
      }
      trains = trains->next;
    }
    currStnConnInfo = currStnConnInfo->next;
  }
  listOfObjects<BFSnode *> *tail;
  tail = q;
  trains_available = BFS(q, tail, source_index, dest_index, adjacency, trains_available, trains_available_tail); // Calling BFS from the source station
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

// The recursive function which performs BFS and returns a list of TrainInfoPerStation with direct journies
listOfObjects<TrainInfoPerStation *> *BFS(listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int source_index, int dest_index, StationAdjacencyList *adjacency, listOfObjects<TrainInfoPerStation *> *trains_available, listOfObjects<TrainInfoPerStation *> *trains_available_tail)
{
  if (q != NULL) // Continues while q is not empty
  {
    int index = q->object->stnIndex;
    listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[index].toStations;
    while (currStnConnInfo != NULL)
    {
      if (currStnConnInfo->object->adjacentStnIndex != source_index) // To prevent cycles
      {
        if (currStnConnInfo->object->adjacentStnIndex == dest_index) // If destination found add to trains_available list
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
          if (node->object->trains != NULL)
          {
            tail->next = node;
            tail = node;
          }
        }
      }
      currStnConnInfo = currStnConnInfo->next;
    }
    q = q->next;
    trains_available = BFS(q, tail, source_index, dest_index, adjacency, trains_available, trains_available_tail); // The recursive call
  }
  return trains_available;
}
