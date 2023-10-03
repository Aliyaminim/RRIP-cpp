/* Static Re-Reference Interval Prediction(RRIP) Cache Replacement: driver program */

#include <cassert>
#include "rrip.hpp"

int slow_get_page_int(int key) {
    return key;
}

int main() {
    size_t cache_size; //cache size
    int n;    //number of upcoming elements

    std::cin >> cache_size >> n;
    assert(std::cin.good());

    caches::rrip_cache<int, int> c_rrip(cache_size);

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
     
    assert((hits_rrip >= 0) && "Number of cache hits should be positive");
    
    std::cout << "RRIP cache hits: " << hits_rrip << std::endl;
    return 0;
}
