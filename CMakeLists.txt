cmake_minimum_required(VERSION 3.13)

project(cache_)

set(CMAKE_CXX_STANDARD 20)

# boost support
#include(cmake/find-boost.cmake)

# build flags
include(cmake/build-flags.cmake)

# collecting libs
add_subdirectory(lib)
message(STATUS "Collected libs: ${LIBLIST}")

# common includes
foreach(LIB ${LIBLIST})
  target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB})
  target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endforeach()

#main
add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/main)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main ${LIBLIST})
install(TARGETS main DESTINATION bin)

install()

#cmake -DCMAKE_BUILD_TYPE=Debug(Release)