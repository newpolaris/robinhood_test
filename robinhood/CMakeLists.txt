project(robinhood VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${ROOT_PATH})

add_executable(robinhood main.cpp graphics_input_layout.cpp)
target_include_directories(robinhood PRIVATE "${robinhood_SOURCE_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
