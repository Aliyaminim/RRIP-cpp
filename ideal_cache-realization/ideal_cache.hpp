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
        std::vector<int> arr_of_positions;
    };

    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;

    std::unordered_map<KeyT, cache_node> nodes_info; 
    //store information about all upcoming nodes, which can be easily touched using unordered_map

    std::unordered_map<KeyT, ListIt> hash_;

public: 
    ideal_caches(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    bool lookup_update(KeyT key, T (*slow_get_page)(KeyT)) {
        if ((auto el = nodes_info.find(key)) != nodes_info.end())
            auto cur_node = el.second;
        else {
            std::cout << "Check how you process input, pay attention to forming of nodes_info" << std::endl;
            abort();
        }

        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                if (cur_node.arr_of_positions.size() == 1)
                    return false;
                int reref_pos = cur_node.arr_of_positions[1];
                int maxcache_reref_pos = -1;
                ListIt rm_node;
                for (auto k = cache_.begin(); k != cache_.end(); k++) {
                    if ((int cur_reref_pos = k->arr_of_positions[0]) > maxcache_reref_pos) {
                        maxcache_reref_pos = cur_reref_pos;
                        rm_node = k;
                    }             
                }
                if (maxcache_reref_pos < reref_pos) {
                    cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
                    return false;
                } else {
                    //вытеснение
                }
                    
            } 
            cache_.emplace_back(cur_node);
            ListIt cache_back = std::prev(cache_.end());
            hash_.emplace(key, cache_back);
            cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
            return false;
        } 
        cur_node.arr_of_positions.erase(cur_node.arr_of_positions.begin());
        return true;
    }
};