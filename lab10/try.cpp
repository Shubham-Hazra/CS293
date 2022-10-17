#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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

// Function Prototypes
listOfObjects<TrainInfoPerStation *> *
present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains);
// listOfObjects<BFSobject *> *BFS(int stopovers, listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int source_index, int dest_index, StationAdjacencyList *adjacency, listOfObjects<BFSobject *> *journeys_available, listOfObjects<BFSobject *> *journeys_available_tail);

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

// // The recursive function which performs BFS and returns a list of TrainInfoPerStation with direct journies
listOfObjects<BFSobject *> *Planner::BFS(int stopovers, listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int source_index, int dest_index, StationAdjacencyList *adjacency, listOfObjects<BFSobject *> *journeys_available, listOfObjects<BFSobject *> *journeys_available_tail)
{
    if (q != NULL) // Continues while q is not empty
    {
        int index = q->object->stnIndex;
        cout << "BRUH " << stnNameToIndex.getKeyAtIndex(q->object->stnIndex) << endl;
        listOfObjects<BFSobject *> *ptr = q->object->journies;
        while (ptr != NULL)
        {
            cout << "STOPS " << ptr->object->stopovers << endl;
            printStationInfo(ptr->object->trains);
            ptr = ptr->next;
        }
        listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[index].toStations;
        while (currStnConnInfo != NULL)
        {
            if (currStnConnInfo->object->adjacentStnIndex == source_index) // To prevent cycles
            {
                currStnConnInfo = currStnConnInfo->next;
                continue;
            }
            if (currStnConnInfo->object->adjacentStnIndex == dest_index) // If destination found add to trains_available list
            {
                if (q->object->stnIndex == source_index)
                {
                    listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                    while (trains != NULL)
                    {
                        listOfObjects<BFSobject *> *ptr = q->object->journies;
                        while (ptr != NULL)
                        {
                            listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(ptr->object);
                            if (trains->object->journeyCode == new_object->object->trains_tail->object->journeyCode)
                            {
                                if (journeys_available == NULL)
                                {
                                    journeys_available = new_object;
                                    journeys_available_tail = new_object;
                                    cout << "Journey added bb " << new_object->object->stopovers << endl;
                                    printStationInfo(new_object->object->trains);
                                }
                                else
                                {
                                    journeys_available_tail->next = new_object;
                                    journeys_available_tail = journeys_available_tail->next;
                                    cout << "Journey added cmon " << new_object->object->stopovers << endl;
                                    printStationInfo(new_object->object->trains);
                                }
                            }
                            ptr = ptr->next;
                        }
                        trains = trains->next;
                    }
                }
                else
                {
                    listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                    while (trains != NULL)
                    {
                        listOfObjects<BFSobject *> *ptr = q->object->journies;
                        while (ptr != NULL)
                        {
                            listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(ptr->object);
                            if (trains->object->journeyCode != new_object->object->trains_tail->object->journeyCode)
                            {
                                listOfObjects<TrainInfoPerStation *> *train = present(trains, stationInfo[index]);
                                new_object->object->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                                new_object->object->trains_tail = new_object->object->trains_tail->next;
                                new_object->object->stopovers++;
                                cout << "Stopover increased " << new_object->object->stopovers << endl;
                            }
                            if (new_object->object->stopovers <= stopovers)
                            {
                                if (journeys_available == NULL)
                                {
                                    journeys_available = new_object;
                                    journeys_available_tail = new_object;
                                    cout << stopovers << " Journey added heh " << new_object->object->stopovers << endl;
                                    printStationInfo(new_object->object->trains);
                                    printStationInfo(journeys_available->object->trains);
                                }
                                else
                                {
                                    journeys_available_tail->next = new_object;
                                    journeys_available_tail = journeys_available_tail->next;
                                    cout << "Journey added hah " << new_object->object->stopovers << endl;
                                    printStationInfo(new_object->object->trains);
                                }
                            }
                            ptr = ptr->next;
                        }
                        trains = trains->next;
                    }
                }
            }
            else
            {
                BFSnode *new_node = new BFSnode(currStnConnInfo->object->adjacentStnIndex);
                if (q->object->stnIndex == source_index)
                {
                    listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                    while (trains != NULL)
                    {
                        listOfObjects<BFSobject *> *ptr = q->object->journies;
                        while (ptr != NULL)
                        {
                            BFSobject *new_obj = new BFSobject((*ptr->object));
                            if (trains->object->journeyCode == new_obj->trains_tail->object->journeyCode)
                            {
                                if (new_node->journies == NULL)
                                {
                                    listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                                    new_node->journies = new_object;
                                    new_node->journies_tail = new_object;
                                }
                                else
                                {
                                    listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                                    new_node->journies_tail->next = new_object;
                                    new_node->journies_tail = new_node->journies_tail->next;
                                }
                            }
                            ptr = ptr->next;
                        }
                        trains = trains->next;
                    }
                }
                else
                {
                    listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                    while (trains != NULL)
                    {
                        listOfObjects<BFSobject *> *ptr = q->object->journies;
                        while (ptr != NULL)
                        {
                            BFSobject *new_obj = new BFSobject((*ptr->object));
                            if (trains->object->journeyCode == new_obj->trains_tail->object->journeyCode)
                            {
                                if (new_node->journies == NULL)
                                {
                                    listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                                    new_node->journies = new_object;
                                    new_node->journies_tail = new_object;
                                }
                                else
                                {
                                    listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                                    new_node->journies_tail->next = new_object;
                                    new_node->journies_tail = new_node->journies_tail->next;
                                }
                            }
                            ptr = ptr->next;
                        }
                        trains = trains->next;
                    }
                    // listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                    // while (trains != NULL)
                    // {
                    //   listOfObjects<BFSobject *> *ptr = q->object->journies;
                    //   while (ptr != NULL)
                    //   {
                    //     BFSobject *new_obj = new BFSobject((*ptr->object));
                    //     if (trains->object->journeyCode != new_obj->trains_tail->object->journeyCode)
                    //     {
                    //       listOfObjects<TrainInfoPerStation *> *train = present(trains, stationInfo[index]);
                    //       new_obj->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
                    //       new_obj->trains_tail = new_obj->trains_tail->next;
                    //       new_obj->stopovers++;
                    //     }
                    //     if (new_obj->stopovers <= stopovers)
                    //     {
                    //       if (new_node->journies == NULL)
                    //       {
                    //         listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                    //         new_node->journies = new_object;
                    //         new_node->journies_tail = new_object;
                    //       }
                    //       else
                    //       {
                    //         listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                    //         new_node->journies_tail->next = new_object;
                    //         new_node->journies_tail = new_node->journies_tail->next;
                    //       }
                    //     }
                    //     ptr = ptr->next;
                    //   }
                    //   trains = trains->next;
                    // }
                }
                listOfObjects<BFSnode *> *node = new listOfObjects<BFSnode *>(new_node);
                if (node->object->journies != NULL)
                {
                    tail->next = node;
                    tail = node;
                }
            }
            //   listOfObjects<BFSobject *> *ptr = q->object->journies;
            //   while (ptr != NULL)
            //   {
            //     BFSobject *new_obj = new BFSobject((*ptr->object));
            //     if (q->object->stnIndex == source_index)
            //     {
            //       if (trains->object->journeyCode == new_obj->trains_tail->object->journeyCode)
            //       {
            //         if (journeys_available == NULL)
            //         {
            //           if (new_obj->stopovers <= stopovers)
            //           {
            //             listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //             journeys_available = new_object;
            //             journeys_available_tail = new_object;
            //           }
            //         }
            //         else
            //         {
            //           if (new_obj->stopovers <= stopovers)
            //           {
            //             listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //             journeys_available_tail->next = new_object;
            //             journeys_available_tail = journeys_available_tail->next;
            //           }
            //         }
            //       }
            //     }
            //     else if (trains->object->journeyCode != new_obj->trains_tail->object->journeyCode)
            //     {
            //       listOfObjects<TrainInfoPerStation *> *train = present(trains, stationInfo[index]);
            //       new_obj->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
            //       new_obj->trains_tail = new_obj->trains_tail->next;
            //       new_obj->stopovers++;
            //       if (journeys_available == NULL)
            //       {
            //         if (new_obj->stopovers <= stopovers)
            //         {
            //           listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //           journeys_available = new_object;
            //           journeys_available_tail = new_object;
            //         }
            //       }
            //       else
            //       {
            //         if (new_obj->stopovers <= stopovers)
            //         {
            //           listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //           journeys_available_tail->next = new_object;
            //           journeys_available_tail = journeys_available_tail->next;
            //         }
            //       }
            //     }
            //     else
            //     {
            //       if (journeys_available == NULL)
            //       {
            //         if (new_obj->stopovers <= stopovers)
            //         {
            //           listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //           journeys_available = new_object;
            //           journeys_available_tail = new_object;
            //         }
            //       }
            //       else
            //       {
            //         if (new_obj->stopovers <= stopovers)
            //         {
            //           listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //           journeys_available_tail->next = new_object;
            //           journeys_available_tail = journeys_available_tail->next;
            //         }
            //       }
            //     }
            //     ptr = ptr->next;
            //   }
            //   trains = trains->next;
            // }
            // else
            // {
            //   BFSnode *new_node = new BFSnode(currStnConnInfo->object->adjacentStnIndex);
            //   listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
            //   while (trains != NULL)
            //   {
            //     listOfObjects<BFSobject *> *ptr = q->object->journies;
            //     while (ptr != NULL)
            //     {
            //       BFSobject *new_obj = new BFSobject((*ptr->object));
            //       if (q->object->stnIndex == source_index)
            //       {
            //         if (trains->object->journeyCode == new_obj->trains_tail->object->journeyCode)
            //         {
            //           if (new_node->journies == NULL)
            //           {
            //             if (new_obj->stopovers <= stopovers)
            //             {
            //               listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //               new_node->journies = new_object;
            //               new_node->journies_tail = new_object;
            //             }
            //           }
            //           else
            //           {
            //             if (new_obj->stopovers <= stopovers)
            //             {
            //               listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //               new_node->journies_tail->next = new_object;
            //               new_node->journies_tail = new_node->journies_tail->next;
            //             }
            //           }
            //         }
            //       }
            //       else if (trains->object->journeyCode != new_obj->trains_tail->object->journeyCode)
            //       {
            //         listOfObjects<TrainInfoPerStation *> *train = present(trains, stationInfo[index]);
            //         new_obj->trains_tail->next = new listOfObjects<TrainInfoPerStation *>(train->object);
            //         new_obj->trains_tail = new_obj->trains_tail->next;
            //         new_obj->stopovers++;
            //         if (new_node->journies == NULL)
            //         {
            //           if (new_obj->stopovers <= stopovers)
            //           {
            //             listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //             new_node->journies = new_object;
            //             new_node->journies_tail = new_object;
            //           }
            //         }
            //         else
            //         {
            //           if (new_obj->stopovers <= stopovers)
            //           {
            //             listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
            //             new_node->journies_tail->next = new_object;
            //             new_node->journies_tail = new_node->journies_tail->next;
            //           }
            //         }
            //       }
            //       ptr = ptr->next;
            //     }
            //     trains = trains->next;
            //   }
            //   listOfObjects<BFSnode *> *node = new listOfObjects<BFSnode *>(new_node);
            //   if (node->object->journies != NULL)
            //   {
            //     tail->next = node;
            //     tail = node;
            //   }
            // }
            currStnConnInfo = currStnConnInfo->next;
        }
        q = q->next;
        journeys_available = BFS(stopovers, stationInfo, q, tail, source_index, dest_index, adjacency, journeys_available, journeys_available_tail); // The recursive call
    }
    return journeys_available;
}

void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
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
    listOfObjects<BFSobject *> *journeys_available = NULL;
    listOfObjects<BFSobject *> *journeys_available_tail = NULL;
    BFSnode *new_node = new BFSnode(source_index);
    listOfObjects<BFSnode *> *q = new listOfObjects<BFSnode *>(new_node);
    listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[source_index].toStations;
    listOfObjects<TrainInfoPerStation *> *source_trains = stationInfo[source_index];
    cout << "Source Trains" << endl;
    printStationInfo(source_trains);
    while (currStnConnInfo != NULL) // Population the BFSnode of the source station with trains leaving from the source station
    {
        listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
        while (trains != NULL)
        {
            listOfObjects<TrainInfoPerStation *> *train = present(trains, source_trains);
            if (q->object->journies == NULL)
            {
                BFSobject *new_obj = new BFSobject();
                listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
                new_obj->trains = new_train;
                new_obj->trains_tail = new_train;
                listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                q->object->journies = new_object;
                q->object->journies_tail = new_object;
            }
            else
            {
                BFSobject *new_obj = new BFSobject();
                listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
                new_obj->trains = new_train;
                new_obj->trains_tail = new_train;
                listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                q->object->journies = new_object;
                q->object->journies->next = q->object->journies_tail;
                q->object->journies_tail->prev = q->object->journies;
            }
            trains = trains->next;
        }
        currStnConnInfo = currStnConnInfo->next;
    }
    listOfObjects<BFSnode *> *tail;
    tail = q;
    journeys_available = BFS(maxStopOvers, stationInfo, q, tail, source_index, dest_index, adjacency, journeys_available, journeys_available_tail); // Calling BFS from the source station

    listOfObjects<BFSobject *> *ptr = q->object->journies;
    if (ptr == NULL)
    {
        cout << "No journies available" << endl;
    }
    else
    {
        cout << "Journies available" << endl;
        while (ptr != NULL)
        {
            cout << "STOPS " << ptr->object->stopovers << endl;
            printStationInfo(ptr->object->trains);
            ptr = ptr->next;
        }
    }

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp

    return;
}

#endif
