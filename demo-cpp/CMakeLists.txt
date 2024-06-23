cmake_minimum_required(VERSION 3.5)
project(TouchScrollPhysicsDemoCPP C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
  "${CMAKE_CURRENT_LIST_DIR}/demo.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/touch_scroll_physics_wrapper.cpp"
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib TouchScrollPhysics)
