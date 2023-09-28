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
            std::cout << "Check how you process input, pay attention to forming of nodes_info map" << std::endl;
            abort();
        }

        el->second.arr_of_positions.erase(el->second.arr_of_positions.begin());
        
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                if (el->second.arr_of_positions.size() == 0) {
                    return false; //больше не встретится, уходит
                }
                int reref_pos = el->second.arr_of_positions[0];
                int maxcache_reref_pos = -1;
                NodeIt rm_node;
                for (auto k = cache_.begin(); k != cache_.end(); k++) {
                    if (k->second.arr_of_positions.size() == 0) {
                        maxcache_reref_pos = reref_pos + 1; //it definitely will be replaced
                        rm_node = k;
                        break;
                    }
                    int cur_reref_pos = k->second.arr_of_positions[0];
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
            cache_.emplace_back(el);
            NodeIt cache_back = std::prev(cache_.end());
            hash_.emplace(key, el);
            return false;
        } 

        return true;
    }

    //prints cache
    void print_cache() const {
        for (auto k = cache_.begin(); k != cache_.end(); ++k) {
            std::cout << k->value << " ";
        }
        std::cout << std::endl;
    }


private:

    size_t sz_;

    using NodeIt = typename std::list<std::pair<KeyT, cache_node>>::iterator;
   
    std::list<std::pair<KeyT,NodeIt>> cache_;

    std::unordered_map<KeyT, NodeIt> hash_;
};


/*public: 

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

        el->second.arr_of_positions.erase(el->second.arr_of_positions.begin());
        auto cur_node = el->second;
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                if (cur_node.arr_of_positions.size() == 0) {
                    return false;
                }
                int reref_pos = cur_node.arr_of_positions[0];
                int maxcache_reref_pos = -1;
                ListIt rm_node;
                for (auto k = cache_.begin(); k != cache_.end(); k++) {
                    auto node_data = nodes_info.find(k->key);
                    if (node_data->second.arr_of_positions.size() == 0) {
                        maxcache_reref_pos = reref_pos + 1; //it definitely will be replaced
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
            cache_.emplace_back(el->second);
            ListIt cache_back = std::prev(cache_.end());
            hash_.emplace(key, cache_back);
            return false;
        } 
        return true;
    }

    //prints cache
    void print_cache() const {
        for (auto k = cache_.begin(); k != cache_.end(); k++) {
            std::cout << k->value << " ";
        }
        std::cout << std::endl;
    }


private:

    size_t sz_;

    std::list<cache_node> cache_;
    using ListIt = typename std::list<cache_node>::iterator;

    std::unordered_map<KeyT, ListIt> hash_;*/