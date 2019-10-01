project(multi VERSION 0.1.0)

file(GLOB HEADER_LIST *.h *.hpp)
file(GLOB SOURCE_LIST *.cpp *.mm)
source_group("sources" FILES ${HEADER_LIST} ${SOURCE_LIST})

add_executable(${PROJECT_NAME} ${HEADER_LIST} ${SOURCE_LIST})
