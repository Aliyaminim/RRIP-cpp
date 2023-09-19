#pragma once 

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

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
    std::unordered_map<KeyT, ListIt> hash_;

    cache_node* fst_dist;
    ListIt fst_dist_it;
    ListIt cache_back;

public:

    caches(size_t sz, cache_node* ptr = nullptr) : sz_(sz), fst_dist(ptr) {}

    bool full() const { return (cache_.size() == sz_); }

    bool lookup_update(T value) {
        auto node = new cache_node;
        node->key = value; //?
        node->value = value; 
        node->rrip = RRIPval_LONG;

        auto hit = hash_.find(node->key); 

        if (hit == hash_.end()) {
            if (full()) {
                if (fst_dist == nullptr) {
                    cache_back = next(cache_.end(), -1);
                    int i = RRIPval_DIST - cache_back->rrip;
                    for (auto k = cache_.begin(); k != cache_.end(); k++) {
                        k->rrip += i;
                        if ((k->rrip == RRIPval_DIST) && (fst_dist == nullptr)) {
                            fst_dist = &(*k);
                            fst_dist_it = k;
                        }
                    }
                }
                ListIt help = next(fst_dist_it);
                hash_.erase(fst_dist->key);      
                cache_.erase(fst_dist_it); 

                cache_.emplace(help, *node);
                //help--;
                hash_.emplace(node->key, help);

                //help++;
                fst_dist_it = help;
                fst_dist = &(*fst_dist_it);
                return false;
            } 

            cache_.emplace_front(*node);
            hash_.emplace(node->key, cache_.begin());
            return false;
        } 
        auto eltit = hit->second;
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, next(eltit));
        
        eltit->rrip = RRIPval_NEAR;
        return true;
    }    
    void print_cache() {
        cout << "\n";
        for (auto k = cache_.begin(); k != cache_.end(); k++) {
            cout << k->value << "(" << k->rrip << ") ";
        }
        if (fst_dist != nullptr)
            cout << fst_dist->value;
    }

};