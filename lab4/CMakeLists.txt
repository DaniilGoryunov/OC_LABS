cmake_minimum_required(VERSION 3.17)
project(os_lab_4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(lib1 SHARED ${LIB_DIR}/pi-sin-1.c)
add_library(lib2 SHARED ${LIB_DIR}/pi-sin-2.c)

target_link_libraries(lib1 m)
target_link_libraries(lib2 m)
target_include_directories(lib1 PUBLIC all)
target_include_directories(lib2 PUBLIC all)

add_executable(static static.c)
add_executable(dinamic dinamic.c)

target_link_libraries(static PRIVATE lib1)
target_include_directories(dinamic PRIVATE all)
