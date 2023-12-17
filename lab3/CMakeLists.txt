add_executable(lab3 ./src/parent.cpp main.cpp)

target_include_directories(lab3 PRIVATE include)


add_executable(child3 ./src/child.cpp ./src/parent.cpp)

target_include_directories(child3 PRIVATE include)

add_dependencies(lab3 child3)