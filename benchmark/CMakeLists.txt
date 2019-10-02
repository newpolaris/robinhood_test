project(benchmark VERSION 0.1.0)

include_directories(${ROOT_PATH})
file(GLOB HEADER_LIST *.h *.hpp)
file(GLOB SOURCE_LIST *.cpp *.mm)
source_group("sources" FILES ${HEADER_LIST} ${SOURCE_LIST})

add_executable(${PROJECT_NAME} ${HEADER_LIST} ${SOURCE_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE "cityhash")
