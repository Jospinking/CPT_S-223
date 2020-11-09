/***************************************************************************
 *
 *  Sorting algorithms and counting work - Quicksort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented quicksort
 *
 */

#ifndef __INSTRUMENTED_QS_H
#define __INSTRUMENTED_QS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton
#include <algorithm>

using namespace std;
int partition(vector<int> & a, int low, int high, SortStats & stats)
{
	int i = low-1;
	int j= high+1;
	int pivot = a[(low+high)/2];
	while (true)
	{
		do{
			i++;
		}
		while(a[i] < pivot);

		do{
			j--;
		}
		while(a[j] > pivot);
		if (i >= j)
		{
			return j;
		}
			//swap

		std::swap (a[i],a[j]);

	}
}

void quickSort (vector<int> & a, int low, int high, SortStats & stats)
{
	if (++stats.compares && low < high)
	{
		int pivot = partition(a, low, high, stats);
		quickSort (a, low, pivot, stats);
		quickSort (a, pivot+1, high, stats);

	}
}

void instrumentedQuickSort( vector<int> & a, SortStats & stats )
{
	clock_t time_begin = clock();		// Please leave in place for stats
	quickSort(a, 0, a.size() -1, stats);






	// Begin sorting algorithm

	// Begin your quicksort code here


	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h

	// End sorting algorithm


	clock_t time_end = clock();			// Please leave in place for stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
