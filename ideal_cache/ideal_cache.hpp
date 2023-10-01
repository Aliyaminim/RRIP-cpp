/* Ideal Cache Replacement 
   
   NOTE: If an incoming page is rereferenced later than others in cache, this incoming page 
   will be ignored and cache will remain unchanged*/
#pragma once 

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <deque>
#include <vector>


template <typename T, typename KeyT> class ideal_caches {

private:
    static MINCACHE_REREF_POS = 0;

    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;

    std::unordered_map<KeyT, ListIt> hash_;

public: 

    struct cache_node {
        KeyT key;
        T value;
        std::deque<int> arr_of_positions; //stores request positions
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
        assert((el != nodes_info.end()) && "Check how you process input, pay attention to forming of nodes_info");
        auto &cur_node = el->second;
        cur_node.arr_of_positions.pop_front();
       
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                if (cur_node.arr_of_positions.empty()) {
                    return false;
                }
                int reref_pos = cur_node.arr_of_positions[0];
                int maxcache_reref_pos = MINCACHE_REREF_POS;
                ListIt rm_node;
                for (auto k = cache_.begin(); k != cache_.end(); ++k) {
                    auto node_data = nodes_info.find(k->key);
                    if (node_data->second.arr_of_positions.empty()) {
                        maxcache_reref_pos = reref_pos + 5; //it definitely will be replaced
                        rm_node = k;
                        break;
                    }
                    int cur_reref_pos = node_data->second.arr_of_positions[0];
                    if (cur_reref_pos > maxcache_reref_pos) {
                        maxcache_reref_pos = cur_reref_pos;
                        rm_node = k;
                    }             
                }
                if (maxcache_reref_pos < reref_pos) {
                    return false;
                } else {
                    hash_.erase(rm_node->key);
                    cache_.erase(rm_node);
                }                   
            } 
            cache_.emplace_back(cur_node);
            ListIt cache_back = std::prev(cache_.end());
            hash_.emplace(key, cache_back);
            return false;
        } 
        return true;
    }

    //prints cache
    void print_cache() const {
        for (auto k : cache_) {
            std::cout << k.value << " ";
        }
        std::cout << std::endl;
    }
};
