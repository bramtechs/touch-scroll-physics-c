cmake_minimum_required(VERSION 3.12)
project(TouchScrollPhysicsJNI LANGUAGES C VERSION 0.0.1)

# Find JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Include parent library headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Create the JNI shared library
add_library(touch_scroll_physics_jni SHARED
  com_doomhowl_touchscrollphysics_TouchScroller.c
  com_doomhowl_touchscrollphysics_TouchScroller.h
)

# Link with the C library
target_link_libraries(touch_scroll_physics_jni PRIVATE TouchScrollPhysics ${JNI_LIBRARIES})

# Set output properties
if(UNIX AND NOT APPLE)
  set_target_properties(touch_scroll_physics_jni PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs"
  )
elseif(APPLE)
  set_target_properties(touch_scroll_physics_jni PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs"
    SUFFIX ".dylib"
  )
elseif(WIN32)
  set_target_properties(touch_scroll_physics_jni PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs"
    PREFIX ""
  )
endif()

# Create directory for compiled Java classes
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/classes")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/lib")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/demo")

# Add custom commands to compile Java sources and create separate JAR files
add_custom_command(
  TARGET touch_scroll_physics_jni
  POST_BUILD
  # Compile library class
  COMMAND ${Java_JAVAC_EXECUTABLE} -d "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/lib" 
          "${CMAKE_CURRENT_SOURCE_DIR}/com/doomhowl/touchscrollphysics/TouchScroller.java"
  # Create library JAR
  COMMAND ${Java_JAR_EXECUTABLE} cf "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-lib.jar" 
          -C "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/lib" .
  # Compile demo with both classes included
  COMMAND ${Java_JAVAC_EXECUTABLE} -d "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/demo" 
          "${CMAKE_CURRENT_SOURCE_DIR}/com/doomhowl/touchscrollphysics/TouchScroller.java"
          "${CMAKE_CURRENT_SOURCE_DIR}/com/doomhowl/touchscrollphysics/TouchScrollerDemo.java"
  # Create standalone demo JAR with main class directly specified
  COMMAND ${Java_JAR_EXECUTABLE} cfe "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-demo.jar"
          com.doomhowl.touchscrollphysics.TouchScrollerDemo
          -C "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/demo" .
  COMMENT "Compiling Java sources and creating separate JARs for library and demo"
  VERBATIM
)

# Installation
install(TARGETS touch_scroll_physics_jni
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-lib.jar"
        "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-demo.jar"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}) 