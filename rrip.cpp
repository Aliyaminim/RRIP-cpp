#include <iostream>
#include <cassert>
#include "rrip.hpp"

int slow_get_page_int(int key) {
    return key;
}

int main() {
    size_t m; //cache size
    int n;    //number of upcoming elements

    std::cin >> m >> n;
    assert(std::cin.good());
    caches<int, int> c(m);

    int hits = 0;

    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        
        if (c.lookup_update(q, slow_get_page_int))
            hits++;

        //c.print_cache();
    }

    std::cout << hits << std::endl;
    
}
