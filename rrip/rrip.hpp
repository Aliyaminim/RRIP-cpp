/* A header file to a C++ program which shows implementation of 
   Static Re-Reference Interval Prediction(RRIP) in High Perfomance Cache Replacement */

#pragma once 

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>


template <typename T, typename KeyT> class caches {

    //RRIP value
    static const int RRIPval_DIST = 3;
    static const int RRIPval_LONG = 2;
    static const int RRIPval_NEAR = 0;

    struct cache_node {
        KeyT key;
        T value;
        int rrip = RRIPval_LONG;
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
    caches(size_t sz) : sz_(sz) {}

    //checks if cache is already full
    bool full() const { return (cache_.size() == sz_); };

    //implements RRIP-replacement while looking up update
    bool lookup_update(const KeyT key, T (*slow_get_page)(KeyT)) {

        auto hit = hash_.find(key); 

        if (hit == hash_.end()) {
            if (full()) {
                if (fst_dist == cache_.end()) {
                    ListIt cache_back = std::prev(cache_.end());
                    int i = RRIPval_DIST - cache_back->rrip;
                    for (auto k = cache_.begin(); k != cache_.end(); ++k) {
                        k->rrip += i;
                        if ((k->rrip == RRIPval_DIST) && (fst_dist == cache_.end())) {
                            fst_dist = k;
                        }
                    }
                }
                ListIt second_dist = std::next(fst_dist);
                hash_.erase(fst_dist->key);      
                cache_.erase(fst_dist);

                cache_.emplace(second_dist, key, slow_get_page(key));
                ListIt node_it = std::prev(second_dist);
                hash_.emplace(key, node_it);

                fst_dist = second_dist;
                return false;
            } 

            cache_.emplace_back(key, slow_get_page(key));
            ListIt cache_back = std::prev(cache_.end());
            hash_.emplace(key, cache_back);
            return false;
        } 

        auto eltit = hit->second;
        if (eltit == fst_dist)
            ++fst_dist;

        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit);
        
        eltit->rrip = RRIPval_NEAR;
        return true;
}    

    //prints cache
    void print_cache() const {
        for (auto k = cache_.begin(); k != cache_.end(); ++k) {
            std::cout << k->value << "(" << k->rrip << ") ";
        }
        if (fst_dist != cache_.end())
            std::cout << fst_dist->value;

        std::cout << std::endl;
    }

};