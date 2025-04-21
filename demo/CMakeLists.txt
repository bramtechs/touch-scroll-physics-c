cmake_minimum_required(VERSION 3.5)
project(TouchScrollPhysicsDemos C)
set(CMAKE_C_STANDARD 99)

# C Demo
add_executable(TouchScrollPhysicsDemoC "${CMAKE_CURRENT_LIST_DIR}/demo.c")
target_link_libraries(TouchScrollPhysicsDemoC PRIVATE raylib TouchScrollPhysics)

# Add Java demo if enabled
if(TSCROLL_BUILD_JAVA)
  add_subdirectory(java)
endif()
