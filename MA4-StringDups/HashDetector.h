/*
 *  Brute force detector implementation
 *
 *  Aaron S. Crandall <acrandal@wsu.edu> - 2019
 *
 */

#ifndef __HASH_DETECTOR_H
#define __HASH_DETECTOR_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>        // a C++11 STL std::unordered_map is a hash table

/*
 *  Function to return a list of the strings appearing more than one time in an input vector
 */
std::vector<std::string> find_duplicates_with_hashtable(std::vector<std::string> & strings) {
    std::vector<std::string> dups;

    // MA TODO: Implement the duplicate finder using a hash table (unordered_map)
    std::unordered_map < std::string, int > myMap;

    
    for(auto val : strings){
      myMap[val]++;
    }
    for(auto val : myMap){
      if(val.second > 1){
        dups.push_back(val.first);
      }
    }



    return dups;
    // Note on return here: it's returning to the caller via a move constructor
    // The vector (dups) lives on the stack, but the stored array contents live on the heap
    // When dups is returned, a new vector shall be instantiated using a move constructor
    // The new vector's move constructor is called with dups as the && other object
}




#endif
