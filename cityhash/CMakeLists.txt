cmake_minimum_required(VERSION 3.0.0)
project(cityhash CXX)

add_library(cityhash STATIC city.cc)
add_executable(cityhash-test city-test.cc)
target_include_directories(cityhash PUBLIC "${cityhash_SOURCE_DIR}")
target_link_libraries(cityhash-test PRIVATE "cityhash")
