cmake_minimum_required(VERSION 3.26.3)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(main src/parent.cpp src/utils.cpp main.cpp)
add_executable(child src/child.cpp src/utils.cpp)

target_include_directories(main PRIVATE include)
target_include_directories(child PRIVATE include)

add_executable(lab3_test ../lab3/src/parent.cpp ../lab3/src/utils.cpp lab3_test.cpp)
target_include_directories(lab3_test PRIVATE ../lab3/include)

target_link_libraries(lab3_test PRIVATE GTest::GTest)