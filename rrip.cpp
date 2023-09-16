#include <iostream>
#include <cassert>
#include "rrip.hpp"

using namespace std;

int slow_get_page_int(int page) {
    return page;
}

int main() {
    int hits = 0;
    size_t m; //cache size
    int n;    //number of upcoming elements

    cin >> m >> n;
    assert(cin.good());
    caches::cache_t<int> c{m};

    for (int i = 0; i < n; ++i) {
        int q;
        cin >> q;
        assert(cin.good());
        if (c.lookup_update(q, slow_get_page_int))
            hits += 1;
    }

    cout << hits << endl;
    
}
