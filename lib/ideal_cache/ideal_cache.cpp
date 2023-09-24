/* A C++ program that includes realization of the functions used in
   Ideal Cache Replacement */

#include "ideal_cache.hpp"


template <typename T, typename KeyT>
ideal_caches<T, KeyT>::ideal_caches(size_t sz) : sz_(sz) {}

template <typename T, typename KeyT>
bool ideal_caches<T, KeyT>::full() const { return (cache_.size() == sz_); }

template <typename T, typename KeyT>
bool ideal_caches<T, KeyT>::lookup_update(const KeyT key, T (*slow_get_page)(KeyT)) {
    auto el = nodes_info.find(key);
    if (el == nodes_info.end()) {
        std::cout << "Check how you process input, pay attention to forming of nodes_info" << std::endl;
        abort();
    }

    auto cur_node = el.second;
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
