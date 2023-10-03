/* Ideal Cache Replacement: driver program */

#include "ideal_cache.hpp"

int slow_get_page_int(int key) {
    return key;
}

int main() {
    size_t cache_size; //cache size
    int n;    //number of upcoming elements

    std::cin >> cache_size >> n;
    assert(std::cin.good());

    caches::ideal_cache<int, int> c_ideal(cache_size);

    std::vector<int> req_el;
  
    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        req_el.push_back(q);

        c_ideal.data_fill(q, i);
    }

    int hits_ideal = 0;

    for (int i = 0; i < n; ++i) {
        if (c_ideal.lookup_update(req_el[i], slow_get_page_int)) 
            hits_ideal++;
        
        #ifdef DEBUG
            c_ideal.print_cache();
        #endif
    }
     
    assert((hits_ideal >= 0) && "In ideal_cache realization it wrongly counts hits");
    
    std::cout << "Ideal_cache cache hits: " << hits_ideal << std::endl;
    return 0;
}
