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
    caches<int, int> c(m);
    //vector<T> elements; //for ideal cache 
    //unordered_map <T, pair<int, list <int>>> data;

    for (int i = 0; i < n; ++i) {
        int q;
        cin >> q;
        assert(cin.good());
        //elements.push_back(q);
        
        if (c.lookup_update(q))
            hits += 1;

        //c.print_cache();
    }

    cout << hits << endl;
    
}
