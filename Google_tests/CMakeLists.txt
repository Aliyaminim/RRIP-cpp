project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_tests_run_rrip ../RRIP-realization/rrip.hpp test_rrip.cpp)
#add_executable(Google_tests_run_idealcache ../ideal_cache-realization/ideal_cache.cpp test_idealcache.cpp)
target_link_libraries(Google_tests_run_rrip gtest gtest_main)
#target_link_libraries(Google_tests_run_idealcache gtest gtest_main)