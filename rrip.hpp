#pragma once 

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>


template <typename T, typename KeyT> class caches {

private :

    static const int RRIPval_DIST = 3;
    static const int RRIPval_LONG = 2;
    static const int RRIPval_NEAR = 0;

    struct cache_node {
        KeyT key;
        T value;
        int rrip;
    };

    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;
    ListIt fst_dist = cache_.end(); 

    std::unordered_map<KeyT, ListIt> hash_;

public:

    caches(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    bool lookup_update(KeyT key, T (*slow_get_page)(KeyT)) {
        T value = slow_get_page(key);
        cache_node node = {key, value, RRIPval_LONG};

        auto hit = hash_.find(node.key); 

        if (hit == hash_.end()) {
            if (full()) {
                if (fst_dist == cache_.end()) {
                    ListIt cache_back = std::prev(cache_.end());
                    int i = RRIPval_DIST - cache_back->rrip;
                    for (auto k = cache_.begin(); k != cache_.end(); k++) {
                        k->rrip += i;
                        if ((k->rrip == RRIPval_DIST) && (fst_dist == cache_.end())) {
                            fst_dist = k;
                        }
                    }
                }
                ListIt second_dist = std::next(fst_dist);
                hash_.erase(fst_dist->key);      
                cache_.erase(fst_dist); //when erase happens, iterator???

                cache_.emplace(second_dist, node);
                ListIt node_it = std::prev(second_dist);
                hash_.emplace(node.key, node_it);

                fst_dist = second_dist;
                return false;
            } 

            cache_.emplace_back(node);
            ListIt cache_back = std::prev(cache_.end());
            hash_.emplace(node.key, cache_back);
            return false;
        } 

        auto eltit = hit->second;
        if (eltit == fst_dist)
            fst_dist = std::next(fst_dist);

        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
        
        eltit->rrip = RRIPval_NEAR;
        return true;
    }    

    void print_cache() {
        std::cout << "\n";
        for (auto k = cache_.begin(); k != cache_.end(); k++) {
            std::cout << k->value << "(" << k->rrip << ") ";
        }
        if (fst_dist != cache_.end())
            std::cout << fst_dist->value;
    }

};