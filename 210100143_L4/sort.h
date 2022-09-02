#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int index;
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l); // Define valid constructor
  bool Quicksort(int start, int finish); // Sort the array according to the stored values
  bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation
  bool printArray();
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor

  void swap(Journey* arr,int i,int j); // Function to swap array values at i and j
  int partition(Journey* arr,int start,int end); // Partition function for quicksort
  bool quicksort(Journey* arr,int start,int end); // Function to recursively do quicksort
  bool insertElement(int JourneyCode, int price); // Function to insert elements in array
  int getComparisons(); // Returns the  number of comparisons
};
