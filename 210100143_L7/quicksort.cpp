#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

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
#include <iostream>
#include <time.h>

void quickSort(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *end, bool sortbyday);

listOfObjects<TrainInfoPerStation *> *pivot_chooser(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, int start_index, int end_index, bool sortbyday);

listOfObjects<TrainInfoPerStation *> *partition_day(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b);

listOfObjects<TrainInfoPerStation *> *partition_time(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b);

void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b);

int getday(TrainInfoPerStation *t);

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

// Swap function to swap the values at two pointers.
// Only changes the TrainInfoPerStation pointer values stored in the pointers and no the pointers itself
void swap(listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
	static TrainInfoPerStation *temp;
	temp = a->object;
	a->object = b->object;
	b->object = temp;
}

// The main function call for Quicksort which calls the recursive quicksort
void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
	srand(time(0));
	// // A few static variable declarations
	// static int K = 4; // Parameter to be experimented with
	// static int recursionLevel = -1; // This can be used to find out at which
	//                                 // level of the recursion you are in

	// // Increment recursion level on entering the function
	// recursionLevel++;

	// // If you need to set up additional storage (upto n/K TrainInfoPerStation
	// // elements), it's ok to do it *once* using static variables/array.
	// // Using the static recursionLevel, you can ensure that the storage
	// // allocation is done only the first time Quicksort is called, and not
	// // in every recursive call.
	// //
	// // Note that if you allocate space for upto n/K TrainInfoPerStation in
	// // each recursive call, you will end up using much more than n/K space
	// // overall.  So you MUST NOT allocate space in each recursive call.
	// //
	// // A variable/array defined using static is not created afresh in
	// // each recursive call.  Instead, a single copy of it is maintained
	// // across all recursions.

	// if (recursionLevel == 0) {
	//   // Find length of the list stnInfoList, if needed.
	//   // Allocate additional space for upto n/K TrainInfoPerStation objects
	//   // if needed.
	//   // Do other things that you may want to do only at the beginning
	//   // as a pre-processing step.
	static int level = 0;
	static int K = 4;
	static listOfObjects<TrainInfoPerStation *> *ptr;
	ptr = stnInfoList;
	static int len;
	len = 0;
	if (level == 0)
	{
		while (ptr != NULL)
		{
			len++;
			ptr = ptr->next;
		}
	}
	listOfObjects<TrainInfoPerStation *> *arr[len / K];
	len = 0;
	ptr = stnInfoList;
	if (level == 0)
	{
		while (ptr != NULL)
		{
			if ((len) % K == 0)
			{
				arr[len / K] = ptr;
			}
			len++;
			ptr = ptr->next;
		}
		level++;
	}
	static listOfObjects<TrainInfoPerStation *> *tail;
	ptr = stnInfoList;
	tail = NULL;
	while (ptr != NULL)
	{
		tail = ptr;
		ptr = ptr->next;
	}
	quickSort(arr, stnInfoList, stnInfoList, tail, true);
	ptr = stnInfoList;
	tail = stnInfoList;
	for (int i = 0; i < 7; i++)
	{
		while (tail != NULL && tail->next != NULL && getday(tail->next->object) == i)
		{
			tail = tail->next;
		}
		quickSort(arr, stnInfoList, ptr, tail, false);
		ptr = tail->next;
	}
	level--;
	// Put your code for the core of Quicksort here
	// Decrement recursion level before leaving the function
	// recursionLevel--;
	return;
}

// Pivot chooser which function which gets the pivot in O(K) time
listOfObjects<TrainInfoPerStation *> *pivot_chooser(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, int start_index, int end_index, bool sortbyday)
{
	static int K = 4;
	static int first;
	first = start_index / K;
	static int last;
	last = end_index / K;
	static int index;
	index = first + rand() % (last - first + 1);
	static int steps;
	if (index == first && index == last)
	{
		steps = (start_index - K * first) + rand() % (end_index - start_index + 1);
	}
	else if (index == last)
	{
		steps = rand() % (end_index - last * K + 1);
	}
	else if (index == first)
	{
		steps = (start_index - K * first) + rand() % (K * (first + 1) - start_index + 1);
	}
	else
	{
		steps = rand() % (K + 1);
	}
	static listOfObjects<TrainInfoPerStation *> *ptr;
	ptr = arr[index];
	// ptr = stnInfoList;
	// steps = start_index + rand() % (end_index - start_index + 1);
	for (int i = 0; i < steps; i++)
	{
		ptr = ptr->next;
	}
	// ptr = stnInfoList;
	// for (int i = 0; i < start_index; i++)
	// {
	// 	ptr = ptr->next;
	// }
	return ptr;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
	srand(time(0));
	// // A few static variable declarations
	// static int K = 4; // Parameter to be experimented with
	// static int recursionLevel = -1; // This can be used to find out at which
	//                                 // level of the recursion you are in

	// // Increment recursion level on entering the function
	// recursionLevel++;

	// // If you need to set up additional storage (upto n/K TrainInfoPerStation
	// // elements), it's ok to do it *once* using static variables/array.
	// // Using the static recursionLevel, you can ensure that the storage
	// // allocation is done only the first time Quicksort is called, and not
	// // in every recursive call.
	// //
	// // Note that if you allocate space for upto n/K TrainInfoPerStation in
	// // each recursive call, you will end up using much more than n/K space
	// // overall.  So you MUST NOT allocate space in each recursive call.
	// //
	// // A variable/array defined using static is not created afresh in
	// // each recursive call.  Instead, a single copy of it is maintained
	// // across all recursions.

	// if (recursionLevel == 0) {
	//   // Allocate additional space for upto n/K TrainInfoPerStation objects
	//   // if needed.
	//   // Do other things that you may want to do only at the beginning
	//   // as a pre-processing step.

	// // Put your code for the core of QuicksortSimple here

	// // Decrement recursion level before leaving the function
	// recursionLevel--;
	static int level = 0;
	static int K = 4;
	static listOfObjects<TrainInfoPerStation *> *ptr;
	ptr = stnInfoList;
	static int len;
	len = 0;
	if (level == 0)
	{
		while (ptr != NULL)
		{
			len++;
			ptr = ptr->next;
		}
	}
	listOfObjects<TrainInfoPerStation *> *arr[len / K];
	len = 0;
	ptr = stnInfoList;
	if (level == 0)
	{
		while (ptr != NULL)
		{
			if ((len) % K == 0)
			{
				arr[len / K] = ptr;
			}
			len++;
			ptr = ptr->next;
		}
		level++;
	}
	static listOfObjects<TrainInfoPerStation *> *tail;
	ptr = stnInfoList;
	tail = stnInfoList;
	for (int i = 0; i < start; i++)
	{
		ptr = ptr->next;
	}
	for (int i = 0; i < end; i++)
	{
		tail = tail->next;
	}
	static listOfObjects<TrainInfoPerStation *> *ptr2;
	ptr2 = tail;
	quickSort(arr, stnInfoList, ptr, tail, true);
	tail = ptr;
	for (int i = 0; i < 7; i++)
	{
		while (tail != NULL && tail->prev != ptr2 && tail->next != NULL && getday(tail->next->object) == i)
		{
			tail = tail->next;
		}
		quickSort(arr, stnInfoList, ptr, tail, false);
		ptr = tail->next;
	}
	level--;
	return;
}

// Partition function which makes the partition according to the days
listOfObjects<TrainInfoPerStation *> *partition_day(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
	static listOfObjects<TrainInfoPerStation *> *pivot;
	pivot = stnInfoList;
	static int start_index, end_index;
	start_index = 0;
	static listOfObjects<TrainInfoPerStation *> *start;
	static listOfObjects<TrainInfoPerStation *> *end;
	while (pivot != NULL && pivot != a)
	{
		start_index++;
		pivot = pivot->next;
	}
	end_index = start_index;
	while (pivot != NULL && pivot != b)
	{
		end_index++;
		pivot = pivot->next;
	}
	pivot = pivot_chooser(arr, stnInfoList, start_index, end_index, true);
	if (pivot == NULL)
	{
		return NULL;
	}
	// static listOfObjects<TrainInfoPerStation *> *pivot;
	// static listOfObjects<TrainInfoPerStation *> *start;
	// static listOfObjects<TrainInfoPerStation *> *end;
	// pivot = b;
	start = NULL;
	end = a;
	swap(pivot, b);
	while (end != b)
	{
		if (getday(end->object) < getday(b->object))
		{
			if (start == NULL)
			{
				start = a;
			}
			else
			{
				start = start->next;
			}
			swap(start, end);
		}
		end = end->next;
	}
	if (start == NULL)
	{
		start = a;
	}
	else
	{
		start = start->next;
	}
	swap(b, start);
	return start;
}

// Partition function which makes the partition according to the time
listOfObjects<TrainInfoPerStation *> *partition_time(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *a, listOfObjects<TrainInfoPerStation *> *b)
{
	static listOfObjects<TrainInfoPerStation *> *pivot;
	pivot = stnInfoList;
	static int start_index, end_index;
	start_index = 0;
	static listOfObjects<TrainInfoPerStation *> *start;
	static listOfObjects<TrainInfoPerStation *> *end;
	while (pivot != NULL && pivot != a)
	{
		start_index++;
		pivot = pivot->next;
	}
	end_index = start_index;
	while (pivot != NULL && pivot != b)
	{
		end_index++;
		pivot = pivot->next;
	}
	pivot = pivot_chooser(arr, stnInfoList, start_index, end_index, false);
	if (pivot == NULL)
	{
		return NULL;
	}
	// static listOfObjects<TrainInfoPerStation *> *pivot;
	// static listOfObjects<TrainInfoPerStation *> *start;
	// static listOfObjects<TrainInfoPerStation *> *end;
	// pivot = b;
	start = NULL;
	end = a;
	swap(pivot, b);
	while (end != b)
	{
		if (end->object->arrTime < b->object->arrTime)
		{
			if (start == NULL)
			{
				start = a;
			}
			else
			{
				start = start->next;
			}
			swap(start, end);
		}
		end = end->next;
	}
	if (start == NULL)
	{
		start = a;
	}
	else
	{
		start = start->next;
	}
	swap(b, start);
	return start;
}

// The recursive quicksort function which can sort according to day or time depending on the time
void quickSort(listOfObjects<TrainInfoPerStation *> **arr, listOfObjects<TrainInfoPerStation *> *stnInfoList, listOfObjects<TrainInfoPerStation *> *start, listOfObjects<TrainInfoPerStation *> *end, bool sortbyday)
{
	if ((end != NULL) && (start != NULL) && (start != end) && (start != end->next))
	{
		static listOfObjects<TrainInfoPerStation *> *pivot_ptr;
		if (sortbyday)
		{
			pivot_ptr = partition_day(arr, stnInfoList, start, end);
			quickSort(arr, stnInfoList, start, pivot_ptr->prev, sortbyday);
			quickSort(arr, stnInfoList, pivot_ptr->next, end, sortbyday);
		}
		else
		{
			pivot_ptr = partition_time(arr, stnInfoList, start, end);
			quickSort(arr, stnInfoList, start, pivot_ptr->prev, sortbyday);
			quickSort(arr, stnInfoList, pivot_ptr->next, end, sortbyday);
		}
	}
}

// Function to get the day on which the train runs
int getday(TrainInfoPerStation *t)
{
	for (int i = 0; i < 7; i++)
	{
		if (t->daysOfWeek[i])
		{
			return i;
		}
	}
	return 1;
}

#endif
