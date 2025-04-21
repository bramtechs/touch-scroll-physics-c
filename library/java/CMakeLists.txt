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

# Add custom commands to compile Java sources and create library JAR file
add_custom_command(
  TARGET touch_scroll_physics_jni
  POST_BUILD
  # Compile library classes
  COMMAND ${Java_JAVAC_EXECUTABLE} -d "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/lib" 
          "${CMAKE_CURRENT_SOURCE_DIR}/com/doomhowl/touchscrollphysics/TouchScroller.java"
          "${CMAKE_CURRENT_SOURCE_DIR}/com/doomhowl/touchscrollphysics/NativeLibLoader.java"
  # Create library JAR
  COMMAND ${Java_JAR_EXECUTABLE} cf "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-lib.jar" 
          -C "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/lib" .
  COMMENT "Compiling Java sources and creating library JAR"
  VERBATIM
)

# Installation
install(TARGETS touch_scroll_physics_jni
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-lib.jar"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}) 