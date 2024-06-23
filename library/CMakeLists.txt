cmake_minimum_required(VERSION 3.5)
project(TouchScrollPhysics C)
set(CMAKE_C_STANDARD 99)

add_library(${PROJECT_NAME} STATIC "${CMAKE_CURRENT_LIST_DIR}/touch_scroll_physics.c")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

if (UNIX)
  target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()
