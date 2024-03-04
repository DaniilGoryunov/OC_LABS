include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)


# add_executable(lab1_test lab1_test.cpp ../lab1/src/parent.cpp)

# target_include_directories(lab1_test PRIVATE ../lab1/include)
# target_link_libraries(lab1_test PRIVATE GTest::GTest)

# add_test(lab1_test lab1_test)


# add_executable(lab2_test lab2_test.cpp ../lab2/src/Experiment.cpp)

# target_include_directories(lab2_test PRIVATE ../lab2/include)
# target_link_libraries(lab2_test PRIVATE GTest::GTest)

# add_test(lab2_test lab2_test)


add_executable(lab3_test lab3_test.cpp ../lab3/src/parent.cpp)

target_include_directories(lab3_test PRIVATE ../lab3/include)
target_link_libraries(lab3_test PRIVATE GTest::GTest)

add_test(lab3_test lab3_test)


# add_library(lib1 SHARED ../lab4/src/implementation1.c)
# add_library(lib2 SHARED ../lab4/src/implementation2.c)

# target_include_directories(lib1 PUBLIC ../lab4/include)
# target_include_directories(lib2 PUBLIC ../lab4/include)

# add_executable(lab4_implementation1_test lab4_implementation1_test.cpp)
# add_executable(lab4_implementation2_test lab4_implementation2_test.cpp)

# target_link_libraries(lab4_implementation1_test PRIVATE lib1)
# target_link_libraries(lab4_implementation2_test PRIVATE lib2)

# target_link_libraries(lab4_implementation1_test PRIVATE GTest::GTest)
# target_link_libraries(lab4_implementation2_test PRIVATE GTest::GTest)

# add_test(lab4_implementation1_test lab4_implementation1_test)
# add_test(lab4_implementation2_test lab4_implementation2_test)
