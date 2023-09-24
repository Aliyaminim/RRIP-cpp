/* A header file to a C++ program which shows implementation of 
   Ideal Cache Replacement */
#pragma once 

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>


template <typename T, typename KeyT> class ideal_caches {

private:
   
    struct cache_node {
        KeyT key;
        T value;
        std::vector<int> arr_of_positions; //stores request positions
    };

    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;

    //stores information about all upcoming nodes
    std::unordered_map<KeyT, cache_node> nodes_info; 

    std::unordered_map<KeyT, ListIt> hash_;

public: 
    //constructor
    ideal_caches(size_t sz);

    //checks if cache is already full
    bool full() const;

    //implements RRIP-replacement while looking up update
    bool lookup_update(const KeyT key, T (*slow_get_page)(KeyT));
};