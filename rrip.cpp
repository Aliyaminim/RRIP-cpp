#include <iostream>
#include <cassert>
#include "rrip.hpp"

int slow_get_page_int(int page) {
    return page;
}

int main() {
    int hits = 0;
    size_t m; //cache size
    int n;    //number of upcoming elements

    std::cin >> m >> n;
    assert(std::cin.good());
    caches<int, int> c(m);
    //vector<T> elements; //for ideal cache 
    //unordered_map <T, pair<int, list <int>>> data;

    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        //elements.push_back(q);
        
        if (c.lookup_update(q))
            hits += 1;

        //c.print_cache();
    }

    std::cout << hits << std::endl;
    
}
