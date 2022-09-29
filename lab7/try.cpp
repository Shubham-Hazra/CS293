// #include <bits/stdc++.h>

// using namespace std;

// void swap(int* arr,int i,int j);
// int partition(int* arr,int start,int end);
// bool quicksort(int* arr,int start,int end);

// bool Quicksort(int* array,int start, int finish)
// {
//     // Call appropriate pivot function based on choice
//     // Split into 2 parts based on pivot choice
//     // Recursively keep sorting
//     if(quicksort(array,start,finish))
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
    
// }

// bool quicksort(int* arr,int start,int end)
// {
//     if(start<end)
//     {
//         int part =partition(arr,start,end);
//         if(part==-1)
//         {
//             return false;
//         }
//         quicksort(arr,start,part-1);
//         quicksort(arr,part+1,end);          
//     }
//     else
//     {
//         return false;
//     }
//     return true;

// }


// // Partition function
// // Appropriately calls the pivot function
// // Returns the pivot index
// int partition(int* arr,int start,int end)
// {
//     int pivot = end;
//     int pivot_index=-1;
//     for(int i=start;i<end+1;i++)
//     {
//         if(arr[pivot]==arr[i])
//         {
//             pivot_index=i;
//             break;
//         }
//         else
//         {
//             continue;
//         }
//     }
//     if(pivot_index==-1)
//     {
//         return -1;
//     }
//     swap(arr,pivot_index,end);
//     int index=start;
//     // for(int i=start;i<end;i++)
//     // {
//     //     if(arr[i]<arr[end])
//     //     {
//     //         swap(arr,i,index);
//     //         index++;
//     //     }
//     //     comparisons++;
//     // }
//     // swap(arr,index,end);
//     // return index;
//     int i=start;
//     int j=end-1;
//     while(i < j)
//     {
//         while(arr[i]<=arr[end])
//         {
//             i++;
//         }
        
//         while(arr[end]<arr[j])
//         {
//             j--;
//         }
        
//         if(i<j)
//         {
//             swap(arr,i,j);
//         }
//     }
//     if(arr[end]<arr[i])
//     {
//         swap(arr,end,i);
//     }
//     return i;

// }

// // Function to swap array values at i and j
// void swap(int* arr,int i,int j)
// {
//     int temp;
//     temp = arr[i];
//     arr[i]=arr[j];
//     arr[j]=temp;
// }

// int main()
// {
//     int n;
//     cin>>n;
//     int arr[n];
//     for(int i=0;i<n;i++)
//     {
//         cin>>arr[i];
//     }
//     Quicksort(arr,0,n-1);
//     for(int i=0;i<n;i++)
//     {
//         cout<<arr[i];
//     }
// }

/* C++ implementation of QuickSort */
#include <bits/stdc++.h>
using namespace std;
  
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
  
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i
        = (low
           - 1); // Index of smaller element and indicates
                 // the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
  
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);
  
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
  
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
  
// Driver Code
int main()
{
    // int arr[] = { 10, 7, 8, 9, 1, 5, 1, 3 ,5, 7, 1 };
    // int n = sizeof(arr) / sizeof(arr[0]);
    // quickSort(arr, 0, n - 1);
    // cout << "Sorted array: \n";
    // printArray(arr, n);
    // return 0;
    srand(time(0));
    cout<<rand()<<" "<<rand();
}