/* A C++ program that includes realization of the functions used in
   Ideal Cache Replacement */

#include "ideal_cache.hpp"

int slow_get_page_int(int key) {
    return key;
}

int main() {
    size_t cache_size; //cache size
    int n;    //number of upcoming elements

    std::cin >> cache_size >> n;
    assert(std::cin.good());

    ideal_caches<int, int> c_ideal(cache_size);
    int hits_ideal = 0;
    std::vector<int> req_el;
  

    for (int i = 0; i < n; ++i) {
        int q;
        std::cin >> q;
        assert(std::cin.good());
        
        auto cur_node = c_ideal.nodes_info.find(q);
        if (cur_node != c_ideal.nodes_info.end()) {
            cur_node->second.arr_of_positions.push_back(i);
        } else {
            ideal_caches<int, int>::cache_node new_node = {q, slow_get_page_int(q), {i}};
            c_ideal.nodes_info.emplace(q, new_node);
        }
        req_el.push_back(q);
    }

    for (int i = 0; i < n; ++i) {
        if (c_ideal.lookup_update(req_el[i], slow_get_page_int))
            hits_ideal++;

        //c_ideal.print_cache();
    }
     
    if (hits_ideal < 0) {
        std::cout << "In ideal_cache realization it wrongly counts hits" << std::endl;
        abort();
    }
    std::cout << "Ideal_cache cache hits: " << hits_ideal << std::endl;
    return 0;
}