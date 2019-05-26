cmake_minimum_required(VERSION 3.0.0)
project(robinhood VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_executable(robinhood main.cpp graphics_input_layout.cpp)
target_include_directories(robinhood PRIVATE "${robinhood_SOURCE_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
