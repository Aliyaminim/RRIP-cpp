#include "gtest/gtest.h"
#include "../RRIP-realization/rrip.cpp"
#include <vector>

TEST(group1, first_test){
    int size_cache = 2,  hits_expected = 3, hits_result = 0;
    std::vector <int> vector_element = { 1, 3, 5, 3, 3, 1, 1, 5 };

    caches<int, int> c(size_cache);

    for (int i = 0; i < vector_element.size(); i++){
        int key = vector_element[i];
       
        if (c.lookup_update(key, slow_get_page_int))
            hits_result++;
    }
    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}
