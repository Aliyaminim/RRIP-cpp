/* Static Re-Reference Interval Prediction(RRIP) in High Perfomance Cache Replacement */

#pragma once 

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>

namespace caches {

template <typename T, typename KeyT> class rrip_cache {

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

    //looks for fst_dist and updates if it's necessary
    void look_for_fstdist() {
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
    }

    //deletes from cache and hash node which has RRIPval_DIST and updates fst_dist  
    void delete_cachenode() {
        ListIt second_dist = std::next(fst_dist);
        hash_.erase(fst_dist->key);      
        cache_.erase(fst_dist);
        fst_dist = second_dist;
    }
    
    //inserts new node to both cache and hash
    void insert_node(const KeyT key, T (*slow_get_page)(KeyT)) {
        cache_.emplace(fst_dist, key, slow_get_page(key));
        ListIt node_it = std::prev(fst_dist);
        hash_.emplace(key, node_it);
    }

    //processes cache hit
    void cache_hit(ListIt eltit) {
        if (eltit == fst_dist)
            ++fst_dist;
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit);
     
        eltit->rrip = RRIPval_NEAR;
    }

public:
    //constructor
    explicit rrip_cache(size_t sz) : sz_(sz) {}

    //checks if cache is already full
    bool full() const { return (cache_.size() == sz_); };

    //implements RRIP-replacement while looking up update
    bool lookup_update(const KeyT key, T (*slow_get_page)(KeyT)) {
        auto hit = hash_.find(key); 

        if (hit == hash_.end()) {
            //cache miss
            if (full()) {
                look_for_fstdist();
                delete_cachenode();
            } 
            insert_node(key, slow_get_page);
            return false;
        } 
        //cache hit
        auto eltit = hit->second;
        cache_hit(eltit);
        return true;
    }    

    //prints cache
    void print_cache() const {
        for (auto k : cache_) {
            std::cout << k.value << "(" << k.rrip << ") ";
        }
        if (fst_dist != cache_.end())
            std::cout << fst_dist->value;

        std::cout << std::endl;
    }

};
}