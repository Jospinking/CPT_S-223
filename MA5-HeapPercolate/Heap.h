//***************************************************************************//
//**
//**  Simple Heap implementation
//**    Copyright 2016 - Aaron S. Crandall <acrandal@wsu.edu>
//**     Initial version for microassignments
//**    Copyright 2019 - Aaron S. Crandall <acrandal@wsu.edu>
//**	 Overhauled version for git with google test and GitLab CI testing
//**
//***************************************************************************//

#ifndef __HEAP_H
#define __HEAP_H

#include <vector>
#include <stdexcept>      // std::out_of_range
#include <math.h>         // pow()
#include <string>

/**
 *  Declaring Heap class
 */
template<typename T>
class Heap
{

private:
	std::vector<T> _items;    // Main vector of elements for heap storage

	/**
	 *  Used to take unsorted data and heapify it
	 */
	void buildHeap()
	{
		for (unsigned int i = _items.size() / 2; i >= 0; --i)
		{
			percolateDown(i);
		}
	}

/*********************************************************************/
/********************* Start Microassignment zone ********************/

	/**
	 *  Percolates the item specified at by index down
     *   into its proper location within a heap.
	 *  Used for dequeue operations and array to heap conversions
	 *  MA TODO: Implement percolateDown!
	 */
	void percolateDown(long unsigned int index)
	{
		int length = this->size();

		int leftIndex = (2*index) + 1;
    int rightIndex = (2*index) + 2;

		if(leftIndex >= length)
        return;

		int min_Index = index;

			     if(_items[index] > _items[leftIndex])
			     {
			         min_Index = leftIndex;
			     }

					 if((rightIndex < length) && (_items[min_Index] > _items[rightIndex]))
				     {
				         min_Index = rightIndex;
				     }

				     if(min_Index != index)
				     {
				         int temp = _items[index];
				         _items[index] = _items[min_Index];
				         _items[min_Index] = temp;
				         percolateDown(min_Index);
				     }

	 }


	/**
	 *  Percolate up from a given index to fix heap property
	 *  Used in inserting new nodes into the heap
	 *   MA TODO: Implement percolateUp
	 */
	void percolateUp( long unsigned int current_position )
	{

	int parent = 0;
	int curP = current_position;

	parent = (curP - 1) / 2;

	while (curP != 0)
	{
			if (_items[curP] < _items[parent])
		{
			int temp = _items[curP];
			_items [curP] = _items[parent];
			_items[parent] = temp;

			curP = parent;
			parent = (curP - 1) / 2;
		}
		else
		{
			break;
		}

	}

}


/********************** End Microassigment zone *********************/

public:
	/**
	 *  Default empty constructor
	 */
	Heap()
		{ }


	/**
	 *  Constructor with a vector of elements
	 */
	Heap(const std::vector<T> &unsorted_vector)
	{
		for (unsigned int i = 0; i < unsorted_vector.size(); i++)
		{
			_items.push_back(unsorted_vector[i]);
		}
		buildHeap();
	}


	/**
	 *  Adds a new item to the heap
	 */
	void push(T item)
	{
		long unsigned int current_position = size(); // Get index location
		_items.push_back(item);                 // Add data to end
		percolateUp( current_position );        // Adjust up, as needed
	}


	/**
	 * Returns the top-most item in our heap without
	 *  actually removing the item from the heap
	 */
	T & top()
	{
		if( size() > 0 )
			return _items[0];
		else
			throw std::out_of_range("top() - No elements in heap");
	}


	/**
	 *  Removes minimum value from heap and returns it to the caller
	 */
	void pop()
	{
		long unsigned int last_index = size() - 1;	// Calc last item index
		int root_index = 0;                      // Root index (for readability)

		if( size() == 0 ) {
			throw std::out_of_range("pop() - No elements in heap");
		}

		_items[root_index] = _items[last_index]; // Move last item to root
		_items.erase(_items.end() - 1);          // Erase last element entry

		if( size() > 0 ) {			// Only runs if the heap isn't empty now
			percolateDown(0);       // Fix heap property
		}
	}


	/**
	 *  Returns true if heap is empty, else false
	 */
	bool empty() const
	{
		if( _items.size() == 0 ) {
			return true;
		} else {
			return false;
		}
	}


	/**
	 *  Returns current quantity of elements in heap (N)
	 */
	long unsigned int size() const
	{
		return _items.size();
	}


	/**
	 *  Return heap data in order from the _items vector
	 */
	std::string to_string() const
	{
		std::string ret = "";
		for(unsigned int i = 0; i < _items.size(); i++)
     	{
			ret += std::to_string(_items[i]) + " ";
		}
		return ret;
	}


	/**
	 *  Print out the data in order from the _items vector
	 */
	void print(std::ostream& out=std::cout) const
	{
		for(int i = 0; i < _items.size(); i++)
     	{
			out << _items[i] << " ";
		}

	}


	/**
	 *  Print out the data with array index details from the _items vector
	 */
	void print_array(std::ostream& out=std::cout) const
	{
		for(unsigned int i = 0; i < _items.size(); i++)
		{
			out << "  [x] Heap element [" << i << "]. key="
				<< _items[i] << std::endl;
		}
	}


	/**
 	 *  Print out the tree by levels (kinda pretty?)
 	 */
	void print_pretty(std::ostream& out=std::cout) const
	{
		int rownum = 1;
		out << "   [x] Level #" << rownum  << " -    ";
		for( unsigned int i = 0; i < _items.size(); i++ )
		{
			out << _items[i] << " ";
			if( pow(2, rownum) - 1 == i + 1 )
			{
				rownum++;
				out << std::endl << "   [x] Level #" << rownum  << " -    ";
			}
		}
		out << std::endl;
	}


	/**
	 *  Returns a copy of the _items vector
	 *   Normally, this would be VERY dangerous, but I am forcing a deep copy
	 *   Because it returns a deep copy, there's no way to effect the real heap vector
	 */
	std::vector<T> get_contents() {
		std::vector<T> vec_copy( this->_items );	// Force a copy constructor
		return vec_copy;							// Does a std::move to target in return
	}
};

#endif
