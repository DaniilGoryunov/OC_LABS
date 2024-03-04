cmake_minimum_required(VERSION 3.10)
project(oc_lab_01)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(child source/child.cpp)
add_executable(main source/main.cpp source/parent.cpp source/parent.hpp)

enable_testing()
add_executable(tests source/tests.cpp  source/parent.hpp source/parent.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests)