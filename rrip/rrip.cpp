/* A C++ program that includes realization of the functions used in
   Static Re-Reference Interval Prediction(RRIP) Cache Replacement */

#include "rrip.hpp"

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
    
    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());

        if (c_rrip.lookup_update(q, slow_get_page_int))
            hits_rrip++;

        #ifdef DEBUG
            c_rrip.print_cache();
        #endif
    }
     
    if (hits_rrip < 0) {
        std::cout << "In RRIP realization it wrongly counts hits" << std::endl;
        abort();
    }
    std::cout << "RRIP cache hits: " << hits_rrip << std::endl;
    return 0;
}
