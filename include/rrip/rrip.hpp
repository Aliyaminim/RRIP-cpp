/* A header file to a C++ program which shows implementation of 
   Static Re-Reference Interval Prediction(RRIP) in High Perfomance Cache Replacement */

#pragma once 

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>


template <typename T, typename KeyT> class caches {

private :
    //RRIP value
    static const int RRIPval_DIST = 3;
    static const int RRIPval_LONG = 2;
    static const int RRIPval_NEAR = 0;

    struct cache_node {
        KeyT key;
        T value;
        int rrip;
    };

    //size of cache
    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;
    //iterator to the first element with RRIPval_DIST 
    ListIt fst_dist = cache_.end(); 

    std::unordered_map<KeyT, ListIt> hash_;

public:
    //constructor
    caches(size_t sz);

    //checks if cache is already full
    bool full() const;

    //implements RRIP-replacement while looking up update
    bool lookup_update(const KeyT key, T (*slow_get_page)(KeyT));  

    //prints cache
    void print_cache() const;

};