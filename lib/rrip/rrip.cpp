/* A C++ program that includes realization of the functions used in
   Static Re-Reference Interval Prediction(RRIP) Cache Replacement */

#include "rrip.hpp"

template <typename T, typename KeyT>
caches<T, KeyT>::caches(size_t sz) : sz_(sz) {}

template <typename T, typename KeyT>
bool caches<T, KeyT>::full() const { return (cache_.size() == sz_); }

template <typename T, typename KeyT>
bool caches<T, KeyT>::lookup_update(const KeyT key, T (*slow_get_page)(KeyT)) {
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
            cache_.erase(fst_dist);

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

template <typename T, typename KeyT>
void caches<T, KeyT>::print_cache() const {
    std::cout << "\n";
    for (auto k = cache_.begin(); k != cache_.end(); k++) {
        std::cout << k->value << "(" << k->rrip << ") ";
    }
    if (fst_dist != cache_.end())
        std::cout << fst_dist->value;
}
