cmake_minimum_required (VERSION 3.20)

set(PROJECT_NAME Tinu8)

project(${PROJECT_NAME})

set(SRC_FILES 
main.cpp
utils.cpp
utf8.cpp
)

set(INCLUDE_DIRS
${CMAKE_CURRENT_LIST_DIR}
)

add_executable (${PROJECT_NAME} ${SRC_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

include_directories(${INCLUDE_DIRS})