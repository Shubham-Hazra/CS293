#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

  // insert your code here
  StationAdjacencyList source;
  for (int i = 0; i < DICT_SIZE; i++)
  {
    if (stnNameToIndex.getKeyAtIndex(adjacency[i].fromStations->object->adjacentStnIndex) == srcStnName)
    {
      source = adjacency[i];
    }
  }

  cout << "No direct journeys available" << endl;

  return;
}
