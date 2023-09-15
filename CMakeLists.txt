cmake_minimum_required(VERSION 3.26)
project(lab1_linked_list C)

set(CMAKE_C_STANDARD 23)

add_executable(lab1_linked_list
        src/main.c
        include/node.h
        include/common.h
        src/common.c
)
# Link the math library (-lm)
target_link_libraries(lab1_linked_list PRIVATE m)