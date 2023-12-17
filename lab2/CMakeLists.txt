add_executable(
               blur 
               main.c 
               include/blur.h src/blur.c 
               include/barrier.h src/barrier.c
               )

target_link_libraries(blur m dl)
target_include_directories(blur PRIVATE include)
