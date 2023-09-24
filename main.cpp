/* A C++ program which shows implementation of 
   Static Re-Reference Interval Prediction(RRIP) in High Perfomance Cache Replacement  
   and compares number of hits in RRIP with ideal cache*/


#include "main.hpp"
#include "rrip/rrip.hpp"
#include "ideal_cache/ideal_cache.hpp"

int slow_get_page_int(int key) {
    return key;
}

int main() {
    size_t cache_size; //cache size
    int n;    //number of upcoming elements

    std::cin >> cache_size >> n;
    assert(std::cin.good());

    caches<int, int> c_rrip(cache_size);
    int hits_rrip = 0;

    ideal_caches<int, int> c_ideal(cache_size);
    int hits_ideal = 0;
    vector<int> req_el;
  

    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        
        auto cur_node = c_ideal.nodes_info.find(q);
        if (cur_node != c_ideal.nodes_info.end()) {
            cur_node->second.arr_of_positions.push_back(i);
        } else {
            cache_node new_node = {q, slow_get_page_int(q), i};
            c_ideal.nodes_info.emplace(q, new_node);
        }
        req_el.push_back(q);

        if (c_rrip.lookup_update(q, slow_get_page_int))
            hits_rrip++;
    }

    for (int i = 0; i < n; ++i) {
        if (c_ideal.lookup_update(req_el[i], slow_get_page_int))
            hits_ideal++;
    }
     
    if ((hits_ideal < 0) || (hits_rrip)) {
        std::cout << "wrongly count hits" << std::endl;
        abort();
    }
    std::cout << "Number of cache hits:\n"<< "RRIP " 
              << hits_rrip << "\nIdeal cache "
              << hits_ideal << std::endl;
    return 0;
}
