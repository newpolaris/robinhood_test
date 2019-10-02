cmake_minimum_required(VERSION 3.0.0)
project(robinhood VERSION 0.1.0)

set(ROOT_PATH "${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(murmur)
add_subdirectory(multi)
add_subdirectory(cityhash)
add_subdirectory(robinhood)
