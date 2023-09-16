#pragma once 

#include <iterator>
#include <stdlib.h>
#include <list>
#include <unordered_map>
#include <vector>

static const int RRIPval_DIST = 3;
static const int RRIPval_LONG = 2;
static const int RRIPval_NEAR = 0;

namespace caches {

template <typename T, typename KeyT = int> struct cache_t {
    size_t sz_;
    using cache_node = typename std::pair<KeyT, std::pair<T, int>>;
    std::list<cache_node> cache_;

    using ListIt = typename std::list<cache_node>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    ListIt fst_dist = cache_.end();

    cache_t(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    bool lookup_update(T page, KeyT hash_func(int)) {
        KeyT key = hash_func(page);

        //
        cache_node node = new cache_node;
        node.first = key;
        node.second.first = page; 
        node.second.second = RRIPval_LONG;
        //

        auto hit = hash_.find(key); 

        if (hit == hash_.end()) {
            if (full()) {
                if (fst_dist == cache_.end()) {
                    int i = RRIPval_DIST - cache_.end()->second.second;
                    for (auto k = cache_.begin(); k != cache_.end(); k++) {
                        k->second.second += i;
                        if (k->second.second == RRIPval_DIST)
                            fst_dist = k;
                    }
                }
                ListIt help = next(fst_dist);
                hash_.erase(fst_dist->first);      
                cache_.erase(fst_dist); 

                cache_.emplace(help, node);
                hash_.emplace(key, *node);
                return false;
            } 

            cache_.emplace_front(node);
            hash_.emplace(key, *node);
            return false;
        } 
        auto eltit = hit->second;
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
        
        eltit->second.second = RRIPval_NEAR;
        return true;
    }    
};
}