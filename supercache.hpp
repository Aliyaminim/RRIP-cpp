#pragma once 

#include <iterator>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>

namespace supercache {
    template <typename S> struct id_cache{
        vector<S> elements; //for ideal cache 
        unordered_map <int, pair<int, list <int>>> data;

        

    };
}