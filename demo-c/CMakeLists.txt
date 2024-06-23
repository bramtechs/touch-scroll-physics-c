cmake_minimum_required(VERSION 3.5)
project(TouchScrollPhysicsDemoC C)
set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}/demo.c")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib TouchScrollPhysics)
