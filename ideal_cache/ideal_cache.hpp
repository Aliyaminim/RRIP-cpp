/* A header file to a C++ program which shows implementation of 
   Ideal Cache Replacement */
#pragma once 

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>


template <typename T, typename KeyT> class ideal_caches {

public: 

    struct cache_node {
        KeyT key;
        T value;
        std::vector<int> arr_of_positions; //stores request positions
    };

    //stores information about all upcoming nodes
    std::unordered_map<KeyT, cache_node> nodes_info; 

    //constructor
    ideal_caches(size_t sz) : sz_(sz) {}

    //checks if cache is already full
    bool full() const { return (cache_.size() == sz_); };

    //implements RRIP-replacement while looking up update
    bool lookup_update(const KeyT key, T (*slow_get_page)(KeyT)) {
        auto el = nodes_info.find(key);
        if (el == nodes_info.end()) {
            std::cout << "Check how you process input, pay attention to forming of nodes_info" << std::endl;
            abort();
        }

        auto cur_node = el->second;
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                if (cur_node.arr_of_positions.size() == 1) {
                    cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
                    return false;
                }
                int reref_pos = cur_node.arr_of_positions[1];
                int maxcache_reref_pos = -1;
                ListIt rm_node;
                for (auto k = cache_.begin(); k != cache_.end(); k++) {
                    int cur_reref_pos = k->arr_of_positions[0];
                    if (cur_reref_pos > maxcache_reref_pos) {
                        maxcache_reref_pos = cur_reref_pos;
                        rm_node = k;
                    }             
                }
                if (maxcache_reref_pos < reref_pos) {
                    cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
                    return false;
                } else {
                    hash_.erase(rm_node->key);
                    cache_.erase(rm_node);
                }                   
            } 
            cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
            cache_.emplace_back(cur_node);
            ListIt cache_back = std::prev(cache_.end());
            hash_.emplace(key, cache_back);
            return false;
        } 
        cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
        return true;
    }

    //prints cache
    void print_cache() const {
        std::cout << "\n";
        for (auto k = cache_.begin(); k != cache_.end(); k++) {
            std::cout << k->value << " ";
        }
        std::cout << std::endl;
    }


private:

    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;

    std::unordered_map<KeyT, ListIt> hash_;
};