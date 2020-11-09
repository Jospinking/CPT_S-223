/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTED_MS_H
#define __INSTRUMENTED_MS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;


void merge(vector <int> & a, int low, int mid, int high, SortStats & stats) {
	int temp[high - low + 1];
	int i = low;
	int j = mid+1;
 	int k = 0;

	while(++stats.compares && i <= mid && j <= high) {
		if(a[i] <= a[j]) {
			temp[k] = a[i];
			k = k + 1;
			i = i + 1;
		}
		else {
			temp[k] = a[j];
			k = k + 1;
			j = j + 1;
		}
	}
	while(++stats.compares && i <= mid) {
		stats.moves++;
		temp[k] = a[i];
		k = k + 1;
		i = i + 1;
	}
	while(++stats.compares && j <= high) {
		stats.moves++;

		temp[k] = a[j];
		k = k + 1;
		j = j + 1;
	}

	for(i = low; stats.compares++ && i <= high; i += 1) {
		stats.moves++;
		a[i] = temp[i - low];
	}
}


void mergeSort(vector<int> & a, int low, int high, SortStats & stats) {

	if(++stats.compares && low < high) {

		int mid = (low + high) / 2;
		mergeSort(a, low, mid, stats);
		mergeSort(a, mid+1, high, stats);
		merge(a, low, mid, high, stats);
	}
}

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    clock_t time_begin = clock();		// Please leave in place for stats

	// Begin sorting algorithm


	// Begin your merge sort code here

	// You're free to add more functions if you like, but vector<int> a must be sorted when done
	// NOTE: you must update stats with comparisons and moves as your algorithm runs
	//  The best example of updating the stats is available in the file:
	//  instrumentedBubbleSort.h
	mergeSort(a, 0, a.size()-1, stats);

	// End sorting algorithm

    clock_t time_end = clock();			// Please leave in place for stats
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
