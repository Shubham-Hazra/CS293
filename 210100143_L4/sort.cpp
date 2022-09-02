#include <iostream>
#include "sort.h"
// Code up the functions defined in sort.cpp


// Constructor function
SorterTree::SorterTree(int choice, int l)
{
    this->choice = choice;
    this->l=l;
    index=0;
    array = new Journey[l];
    comparisons=0;
    tree = new BST();
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    if(quicksort(array,start,finish))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool SorterTree::quicksort(Journey* arr,int start,int end)
{
    if(start<end)
    {
        int part =partition(arr,start,end);
        if(part==-1)
        {
            return false;
        }
        quicksort(arr,start,part-1);
        quicksort(arr,part+1,end);          
    }
    else
    {
        return false;
    }
    return true;

}


// Partition function
// Appropriately calls the pivot function
// Returns the pivot index
int SorterTree::partition(Journey* arr,int start,int end)
{
    Journey* pivot;
    if(choice==1)
    {
        pivot = choose_one(arr,start,end);
    }
    else if(choice==2)
    {
        pivot = choose_two(arr,start,end);
    }
    else if(choice==3)
    {
        pivot = choose_three(arr,start,end);
    }
    int pivot_index=-1;
    for(int i=start;i<end+1;i++)
    {
        if(pivot->getJourneyCode()==arr[i].getJourneyCode())
        {
            pivot_index=i;
            break;
        }
        else
        {
            continue;
        }
    }
    if(pivot_index==-1)
    {
        return -1;
    }
    swap(arr,pivot_index,end);
    int index=start;
    // for(int i=start;i<end;i++)
    // {
    //     if(arr[i]<arr[end])
    //     {
    //         swap(arr,i,index);
    //         index++;
    //     }
    //     comparisons++;
    // }
    // swap(arr,index,end);
    // return index;
    int i=start;
    int j=end-1;
    while(i < j)
    {
        while(arr[i]<arr[end])
        {
            i++;
            comparisons++;
        }
        comparisons++;
        
        while(arr[end]<arr[j])
        {
            j--;
            comparisons++;
        }
        comparisons++;
        
        if(i<j)
        {
            swap(arr,i,j);
        }
    }
    if(arr[end]<arr[i])
    {
        swap(arr,end,i);
    }
    comparisons++;
    return i;

}

// Function to swap array values at i and j
void SorterTree::swap(Journey* arr,int i,int j)
{
    Journey temp;
    temp = arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    if(start<finish)
    {
        int pivot_index=partition(array,start,finish);
        if(pivot_index==-1)
        {
            return false;
        }
        tree->insert(array[pivot_index].getJourneyCode(),array[pivot_index].getPrice());
        QuicksortWithBSTInsert(start,pivot_index-1);
        QuicksortWithBSTInsert(pivot_index+1,finish);
    }
    else if(start==finish)
    {
        tree->insert(array[start].getJourneyCode(),array[start].getPrice());
        return true;
    }
    return true;

}


// Prints the array
bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
    return true;
}

// Inserts Journey into the BST
bool SorterTree::insertPivot(int JourneyCode, int price)
{
    return tree->insert(JourneyCode,price);
}

// Inserts journey into the array
bool SorterTree::insertElement(int JourneyCode, int price)
{
    if(index<l)
    {
        Journey j = Journey(JourneyCode,price);
        array[index]=j;
        index++;
        return true;
    }
    else
    {
        return false;
    }
   
}

// Returns the number of comparisons
int SorterTree::getComparisons()
{
    return comparisons;
}

// Returns a pointer to the tree
BST* SorterTree::getTree()
{
    return tree;
}

//Destructor function
SorterTree::~SorterTree(){}