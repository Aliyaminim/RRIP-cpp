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

namespace caches {

template <typename T, typename KeyT> class ideal_cache {

private:
    static const int MINCACHE_REREF_POS_ = 0;
    static const int MAXCACHE_REREF_POS_ = 2147483647;

    size_t sz_;

    struct cache_node_ {
        KeyT key;
        T value;
    };

    std::list<cache_node_> cache_;
    using ListIt = typename std::list<cache_node_>::iterator;

    std::unordered_map<KeyT, ListIt> hash_;

    struct node_data_ {
        KeyT key;
        std::deque<int> arr_of_positions; //stores request positions
    };

    //stores information about all upcoming nodes
    std::unordered_map<KeyT, node_data_> nodes_info_; 

    //updates node's data and return it
    node_data_ upd_node_data(const KeyT key) {
        auto el = nodes_info_.find(key);
        assert((el != nodes_info_.end()) && "Check how you process input, pay attention to forming of nodes_info");
        el->second.arr_of_positions.pop_front();
        return el->second;
    }

    //deletes from cache and hash node, which will be rereferenced later than others(see NOTE above)
    bool delete_cachenode (const KeyT key, node_data_ &cur_node) {
        int reref_pos = cur_node.arr_of_positions[0];
        int maxcache_reref_pos = MINCACHE_REREF_POS_;
        ListIt rm_node;
        for (auto k = cache_.begin(); k != cache_.end(); ++k) {
            auto node_data = nodes_info_.find(k->key);
            if (node_data->second.arr_of_positions.empty()) {
                maxcache_reref_pos = MAXCACHE_REREF_POS_; 
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
            return true;
        } 
    }
    
    //inserts new node to both cache and hash
    void insert_node(const KeyT key, T (*slow_get_page)(KeyT)) {
        cache_.emplace_back(key, slow_get_page(key));
        ListIt cache_back = std::prev(cache_.end());
        hash_.emplace(key, cache_back); 
    }

public: 
    //constructor
    explicit ideal_cache(size_t sz) : sz_(sz) {}

    //checks if cache is already full
    bool full() const { return (cache_.size() == sz_); };

    //implements RRIP-replacement while looking up update
    bool lookup_update(const KeyT key, T (*slow_get_page)(KeyT)) {
        auto cur_node = upd_node_data(key);     
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                if (cur_node.arr_of_positions.empty()) {
                    //this page will never be rereferenced, so we ignore it
                    return false; 
                }
                if (delete_cachenode(key, cur_node))
                    insert_node(key, slow_get_page); 
                return false;  
            } 
            insert_node(key, slow_get_page);         
            return false;
        } 
        return true;
    }

    // fills in nodes_info_ unordered map with information about each upcoming key
    void data_fill(KeyT q, int i) {
        auto cur_node = nodes_info_.find(q);
        if (cur_node != nodes_info_.end()) {
            cur_node->second.arr_of_positions.push_back(i);
        } else {
            nodes_info_.emplace(q, node_data_{q, {i}});
        }
    }

    //prints cache
    void print_cache() const {
        for (auto k : cache_) {
            std::cout << k.value << " ";
        }
        std::cout << std::endl;
    }
};
}
