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

class BFSobject
{
public:
    int stopovers;
    listOfObjects<int *> *station_indexes;
    listOfObjects<int *> *station_indexes_tail;
    listOfObjects<TrainInfoPerStation *> *trains;
    listOfObjects<TrainInfoPerStation *> *trains_tail;

    BFSobject()
    {
        stopovers = 0;
        trains = NULL;
        trains_tail = NULL;
        station_indexes = NULL;
        station_indexes_tail = NULL;
    }
};

class BFSnode
{
public:
    int stnIndex;
    listOfObjects<BFSobject *> *journies;
    listOfObjects<BFSobject *> *journies_tail;

    BFSnode(int index)
    {
        stnIndex = index;
        journies = NULL;
        journies_tail = NULL;
    }
};
// Class made to use as the nodes in a queue used for BFS
// Contains information about the index of the station and the trains leaving from the station which also departed from the source station
// Has a doubly linked list of TrainInfoPerStation

// Function Prototypes
listOfObjects<TrainInfoPerStation *> *
present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains);
listOfObjects<BFSobject *> *BFS(int stopovers, listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int source_index, int dest_index, StationAdjacencyList *adjacency, listOfObjects<BFSobject *> *journeys_available, listOfObjects<BFSobject *> *journeys_available_tail);
void printInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<int *> *source_indexes);

// void printInfo(listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<int *> *source_indexes)
// {
//   listOfObjects<TrainInfoPerStation *> *currList, *expandedList;
//   TrainInfoPerStation *currInfo;
//   string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

//   // Expanding information in stnInfoList to get a list of train info
//   // in which each element of the list refers to a single day of the
//   // week.  This is the list that has to be finally sorted using
//   // quicksort.

//   currList = stnInfoList;
//   expandedList = nullptr;
//   int listLength = 0;
//   while (currList != nullptr)
//   {
//     currInfo = currList->object;
//     if (currInfo != nullptr)
//     {
//       // Make as many copies of currInfo as the total count of days in the week
//       // when this train runs from/to this station
//       int jCode = currInfo->journeyCode;
//       int stSeq = currInfo->stopSeq;
//       int arrTime = currInfo->arrTime;
//       int depTime = currInfo->depTime;

//       for (int i = 0; i < 7; i++)
//       {
//         if (currInfo->daysOfWeek[i])
//         {
//           TrainInfoPerStation *newExpandedElement = new TrainInfoPerStation(jCode, stSeq, arrTime, depTime);
//           if (newExpandedElement == nullptr)
//           {
//             cerr << "Memory allocation failure." << endl;
//             continue;
//           }
//           newExpandedElement->setDayOfWeek(i);

//           listOfObjects<TrainInfoPerStation *> *newExpandedListElement = new listOfObjects<TrainInfoPerStation *>(newExpandedElement);
//           if (newExpandedListElement == nullptr)
//           {
//             cerr << "Memory allocation failure." << endl;
//             continue;
//           }

//           if (expandedList == nullptr)
//           {
//             expandedList = newExpandedListElement;
//           }
//           else
//           {
//             newExpandedListElement->next = expandedList;
//             expandedList->prev = newExpandedListElement;
//             expandedList = newExpandedListElement;
//           }
//           listLength++;
//         }
//       }
//     }
//     currList = currList->next;
//   }
//   currList = expandedList;
//   while (currList != nullptr)
//   {
//     currInfo = currList->object;
//     if (currInfo != nullptr)
//     {
//       cout << GREEN << "Day(s): " << RESET;
//       for (int i = 0; i < 7; i++)
//       {
//         if (currInfo->daysOfWeek[i])
//           cout << days[i] << " ";
//       }
//       cout << endl;
//       cout << BLUE << "JourneyCode: " << currInfo->journeyCode << RESET << "\t";
//       cout << RED << "Arr: " << RESET;
//       if (currInfo->arrTime == -1)
//       {
//         cout << "Starts";
//       }
//       else
//       {
//         cout << currInfo->arrTime;
//       }
//       cout << RED << " Dep: " << RESET;
//       if (currInfo->depTime == -1)
//       {
//         cout << "Ends";
//       }
//       else
//       {
//         cout << currInfo->depTime;
//       }
//       cout << endl;
//     }
//     currList = currList->next;
//     index = index->next;
//   }
//   cout << endl;
// }
// Function to search for a train in a given list of trains(Using journey codes)
// If found returns the TrainInfoPerStation object from the list else returns nullptr
listOfObjects<TrainInfoPerStation *> *present(listOfObjects<TrainInfoPerStation *> *train, listOfObjects<TrainInfoPerStation *> *trains)
{
    while (trains != nullptr)
    {
        if (trains->object->journeyCode == train->object->journeyCode)
        {
            listOfObjects<TrainInfoPerStation *> *train_copy = new listOfObjects<TrainInfoPerStation *>(trains->object);
            return train_copy;
        }
        trains = trains->next;
    }
    return nullptr;
}

// // The recursive function which performs BFS and returns a list of TrainInfoPerStation with direct journies
listOfObjects<BFSobject *> *BFS(int stopovers, listOfObjects<TrainInfoPerStation *> **stationInfo, listOfObjects<BFSnode *> *q, listOfObjects<BFSnode *> *tail, int source_index, int dest_index, StationAdjacencyList *adjacency, listOfObjects<BFSobject *> *journeys_available, listOfObjects<BFSobject *> *journeys_available_tail)
{
    if (q != nullptr) // Continues while q is not empty
    {
        int index = q->object->stnIndex;
        listOfObjects<BFSobject *> *ptr = q->object->journies;
        while (ptr != nullptr)
        {
            ptr = ptr->next;
        }
        listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[index].toStations;
        while (currStnConnInfo != nullptr)
        {
            if (currStnConnInfo->object->adjacentStnIndex == dest_index) // If destination found add to trains_available list
            {
                if (q->object->stnIndex == source_index && q->object->journies->next == NULL)
                {
                    listOfObjects<BFSobject *> *ptr = q->object->journies;
                    while (ptr != nullptr)
                    {
                        listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(ptr->object);
                        listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                        while (trains != nullptr)
                        {
                            if (trains->object->journeyCode == new_object->object->trains->object->journeyCode)
                            {
                                if (new_object->object->stopovers <= stopovers)
                                {
                                    if (journeys_available == nullptr)
                                    {
                                        journeys_available = new_object;
                                        journeys_available_tail = new_object;
                                    }
                                    else
                                    {
                                        journeys_available_tail->next = new_object;
                                        journeys_available_tail = journeys_available_tail->next;
                                    }
                                }
                            }
                            trains = trains->next;
                        }
                        ptr = ptr->next;
                    }
                }
                else
                {
                    listOfObjects<BFSobject *> *ptr = q->object->journies;
                    while (ptr != nullptr)
                    {
                        listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                        while (trains != nullptr)
                        {
                            BFSobject *new_obj = new BFSobject();
                            listOfObjects<TrainInfoPerStation *> *t = ptr->object->trains;
                            while (t != nullptr)
                            {
                                if (new_obj->trains == nullptr)
                                {
                                    listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                                    new_obj->trains = tr;
                                    new_obj->trains_tail = tr;
                                }
                                else
                                {
                                    listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                                    new_obj->trains_tail->next = tr;
                                    new_obj->trains_tail = new_obj->trains_tail->next;
                                }
                                t = t->next;
                            }
                            listOfObjects<int *> *i = ptr->object->station_indexes;
                            while (i != nullptr)
                            {
                                if (new_obj->station_indexes == nullptr)
                                {
                                    listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                                    new_obj->station_indexes = ij;
                                    new_obj->station_indexes_tail = ij;
                                }
                                else
                                {
                                    listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                                    new_obj->station_indexes_tail->next = ij;
                                    new_obj->station_indexes_tail = new_obj->station_indexes_tail->next;
                                }
                                i = i->next;
                            }
                            new_obj->stopovers = ptr->object->stopovers;
                            listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                            if (trains->object->journeyCode != new_object->object->trains->object->journeyCode)
                            {
                                if (new_object->object->stopovers < stopovers)
                                {
                                    listOfObjects<TrainInfoPerStation *> *train = present(trains, stationInfo[index]);
                                    listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(trains->object);
                                    // new_train->next = new_object->object->trains;
                                    // new_object->object->trains->prev = new_train;
                                    // new_object->object->trains = new_train;
                                    new_object->object->trains_tail->next = new_train;
                                    new_train->prev = new_object->object->trains_tail;
                                    new_object->object->trains_tail = new_object->object->trains_tail->next;
                                    int *num = new int(q->object->stnIndex);
                                    listOfObjects<int *> *new_int = new listOfObjects<int *>(num);
                                    new_object->object->station_indexes_tail->next = new_int;
                                    new_int->prev = new_object->object->station_indexes_tail;
                                    new_object->object->station_indexes_tail = new_object->object->station_indexes_tail->next;
                                    new_object->object->stopovers++;
                                    if (journeys_available == nullptr)
                                    {
                                        journeys_available = new_object;
                                        journeys_available_tail = new_object;
                                    }
                                    else
                                    {
                                        journeys_available_tail->next = new_object;
                                        journeys_available_tail = journeys_available_tail->next;
                                    }
                                }
                            }
                            else
                            {
                                if (new_object->object->stopovers <= stopovers)
                                {
                                    if (journeys_available == nullptr)
                                    {
                                        journeys_available = new_object;
                                        journeys_available_tail = new_object;
                                    }
                                    else
                                    {
                                        journeys_available_tail->next = new_object;
                                        journeys_available_tail = journeys_available_tail->next;
                                    }
                                }
                            }
                            trains = trains->next;
                        }
                        ptr = ptr->next;
                    }
                }
            }
            else
            {
                BFSnode *new_node = new BFSnode(currStnConnInfo->object->adjacentStnIndex);
                if (q->object->stnIndex == source_index && q->object->journies->next == NULL)
                {
                    listOfObjects<BFSobject *> *ptr = q->object->journies;
                    while (ptr != nullptr)
                    {
                        listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                        while (trains != nullptr)
                        {
                            BFSobject *new_obj = new BFSobject();
                            listOfObjects<TrainInfoPerStation *> *t = ptr->object->trains;
                            while (t != nullptr)
                            {
                                if (new_obj->trains == nullptr)
                                {
                                    listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                                    new_obj->trains = tr;
                                    new_obj->trains_tail = tr;
                                }
                                else
                                {
                                    listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                                    new_obj->trains_tail->next = tr;
                                    new_obj->trains_tail = new_obj->trains_tail->next;
                                }
                                t = t->next;
                            }
                            listOfObjects<int *> *i = ptr->object->station_indexes;
                            while (i != nullptr)
                            {
                                if (new_obj->station_indexes == nullptr)
                                {
                                    listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                                    new_obj->station_indexes = ij;
                                    new_obj->station_indexes_tail = ij;
                                }
                                else
                                {
                                    listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                                    new_obj->station_indexes_tail->next = ij;
                                    new_obj->station_indexes_tail = new_obj->station_indexes_tail->next;
                                }
                                i = i->next;
                            }
                            listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                            if (trains->object->journeyCode == new_object->object->trains->object->journeyCode)
                            {
                                if (new_node->journies == nullptr)
                                {
                                    new_node->journies = new_object;
                                    new_node->journies_tail = new_object;
                                }
                                else
                                {

                                    new_node->journies_tail->next = new_object;
                                    new_node->journies_tail = new_node->journies_tail->next;
                                }
                            }
                            trains = trains->next;
                        }
                        ptr = ptr->next;
                    }
                }
                else
                {
                    listOfObjects<BFSobject *> *ptr = q->object->journies;
                    while (ptr != nullptr)
                    {
                        listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
                        while (trains != nullptr)
                        {
                            BFSobject *new_obj = new BFSobject();
                            listOfObjects<TrainInfoPerStation *> *t = ptr->object->trains;
                            while (t != nullptr)
                            {
                                if (new_obj->trains == nullptr)
                                {
                                    listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                                    new_obj->trains = tr;
                                    new_obj->trains_tail = tr;
                                }
                                else
                                {
                                    listOfObjects<TrainInfoPerStation *> *tr = new listOfObjects<TrainInfoPerStation *>(t->object);
                                    new_obj->trains_tail->next = tr;
                                    new_obj->trains_tail = new_obj->trains_tail->next;
                                }
                                t = t->next;
                            }
                            listOfObjects<int *> *i = ptr->object->station_indexes;
                            while (i != nullptr)
                            {
                                if (new_obj->station_indexes == nullptr)
                                {
                                    listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                                    new_obj->station_indexes = ij;
                                    new_obj->station_indexes_tail = ij;
                                }
                                else
                                {
                                    listOfObjects<int *> *ij = new listOfObjects<int *>(i->object);
                                    new_obj->station_indexes_tail->next = ij;
                                    new_obj->station_indexes_tail = new_obj->station_indexes_tail->next;
                                }
                                i = i->next;
                            }
                            new_obj->stopovers = ptr->object->stopovers;
                            listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                            if (trains->object->journeyCode == new_object->object->trains->object->journeyCode)
                            {
                                if (new_object->object->stopovers <= stopovers)
                                {
                                    if (new_node->journies == nullptr)
                                    {

                                        new_node->journies = new_object;
                                        new_node->journies_tail = new_object;
                                    }
                                    else
                                    {
                                        new_node->journies_tail->next = new_object;
                                        new_node->journies_tail = new_node->journies_tail->next;
                                    }
                                }
                            }
                            else
                            {
                                listOfObjects<TrainInfoPerStation *> *train = present(trains, stationInfo[index]);
                                listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(trains->object);
                                // new_train->next = new_object->object->trains;
                                // new_object->object->trains->prev = new_train;
                                // new_object->object->trains = new_train;
                                new_object->object->trains_tail->next = new_train;
                                new_train->prev = new_object->object->trains_tail;
                                new_object->object->trains_tail = new_object->object->trains_tail->next;
                                int *num = new int(q->object->stnIndex);
                                listOfObjects<int *> *new_int = new listOfObjects<int *>(num);
                                new_object->object->station_indexes_tail->next = new_int;
                                new_int->prev = new_object->object->station_indexes_tail;
                                new_object->object->station_indexes_tail = new_int;
                                new_object->object->stopovers++;
                                if (new_object->object->stopovers <= stopovers)
                                {
                                    if (new_node->journies == nullptr)
                                    {

                                        new_node->journies = new_object;
                                        new_node->journies_tail = new_object;
                                    }
                                    else
                                    {
                                        new_node->journies_tail->next = new_object;
                                        new_node->journies_tail = new_node->journies_tail->next;
                                    }
                                }
                            }
                            trains = trains->next;
                        }
                        ptr = ptr->next;
                    }
                }
                listOfObjects<BFSnode *> *node = new listOfObjects<BFSnode *>(new_node);
                if (node->object->journies != nullptr)
                {
                    tail->next = node;
                    tail = node;
                }
            }
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
    listOfObjects<BFSobject *> *journeys_available = nullptr;
    listOfObjects<BFSobject *> *journeys_available_tail = nullptr;
    BFSnode *new_node = new BFSnode(source_index);
    listOfObjects<BFSnode *> *q = new listOfObjects<BFSnode *>(new_node);
    listOfObjects<StationConnectionInfo *> *currStnConnInfo = adjacency[source_index].toStations;
    listOfObjects<TrainInfoPerStation *> *source_trains = stationInfo[source_index];
    while (currStnConnInfo != nullptr) // Population the BFSnode of the source station with trains leaving from the source station
    {
        listOfObjects<TrainInfoPerStation *> *trains = currStnConnInfo->object->trains;
        while (trains != nullptr)
        {
            listOfObjects<TrainInfoPerStation *> *train = present(trains, source_trains);
            if (q->object->journies == nullptr)
            {
                BFSobject *new_obj = new BFSobject();
                listOfObjects<TrainInfoPerStation *> *new_train = new listOfObjects<TrainInfoPerStation *>(train->object);
                int *num = new int(source_index);
                listOfObjects<int *> *new_index = new listOfObjects<int *>(num);
                new_obj->station_indexes = new_index;
                new_obj->station_indexes_tail = new_index;
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
                int *num = new int(source_index);
                listOfObjects<int *> *new_index = new listOfObjects<int *>(num);
                new_obj->station_indexes = new_index;
                new_obj->station_indexes_tail = new_index;
                new_obj->trains = new_train;
                new_obj->trains_tail = new_train;
                listOfObjects<BFSobject *> *new_object = new listOfObjects<BFSobject *>(new_obj);
                new_object->next = q->object->journies;
                q->object->journies->prev = new_object;
                q->object->journies = new_object;
            }
            trains = trains->next;
        }
        currStnConnInfo = currStnConnInfo->next;
    }
    listOfObjects<BFSnode *> *tail;
    tail = q;
    journeys_available = BFS(maxStopOvers, stationInfo, q, tail, source_index, dest_index, adjacency, journeys_available, journeys_available_tail); // Calling BFS from the source station

    listOfObjects<BFSobject *> *ptr = journeys_available;
    if (ptr == nullptr)
    {
        cout << "No journies available" << endl;
    }
    else
    {
        cout << "Journies available" << endl;

        while (ptr != nullptr)
        {
            cout << "STOPS " << ptr->object->stopovers << endl;
            cout << "Stations: " << endl;
            listOfObjects<int *> *stn_ptr = ptr->object->station_indexes;
            listOfObjects<TrainInfoPerStation *> *train = ptr->object->trains;
            while (stn_ptr != NULL)
            {
                cout << stnNameToIndex.getKeyAtIndex(*stn_ptr->object) << " Journey code: " << train->object->journeyCode << endl;
                stn_ptr = stn_ptr->next;
                train = train->next;
            }
            cout << stnNameToIndex.getKeyAtIndex(dest_index) << endl;
            cout << endl;
            // printStationInfo(ptr->object->trains, ptr->object->station_indexes);
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
