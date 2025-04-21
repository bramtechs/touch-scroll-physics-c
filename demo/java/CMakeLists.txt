cmake_minimum_required(VERSION 3.12)
project(TouchScrollPhysicsJavaDemo)

# Find Java
find_package(Java 1.8 REQUIRED)
include(UseJava)

# Create directories for output
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/classes")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/libs")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/native/macos/x86_64")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/native/macos/arm64")

# Add custom command to compile Java sources and create demo JAR
add_custom_target(touch_scroll_physics_java_demo ALL
  # Extract library JAR to demo build/classes to include all library classes
  COMMAND cd "${CMAKE_CURRENT_SOURCE_DIR}/build/classes" && ${Java_JAR_EXECUTABLE} xf "${CMAKE_SOURCE_DIR}/library/java/build/libs/touch-scroll-physics-lib.jar"
  
  # Compile demo with main class
  COMMAND ${Java_JAVAC_EXECUTABLE} -d "${CMAKE_CURRENT_SOURCE_DIR}/build/classes" 
          -cp "${CMAKE_SOURCE_DIR}/library/java/build/libs/touch-scroll-physics-lib.jar"
          "${CMAKE_CURRENT_SOURCE_DIR}/com/doomhowl/touchscrollphysics/TouchScrollerDemo.java"
  
  # Copy the native library to the appropriate location based on platform
  COMMAND ${CMAKE_COMMAND} -E copy 
          "${CMAKE_SOURCE_DIR}/library/java/build/libs/libtouch_scroll_physics_jni.dylib"
          "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/native/macos/x86_64/"
  
  # On macOS, copy to arm64 directory too (if building on ARM)
  COMMAND ${CMAKE_COMMAND} -E copy 
          "${CMAKE_SOURCE_DIR}/library/java/build/libs/libtouch_scroll_physics_jni.dylib"
          "${CMAKE_CURRENT_SOURCE_DIR}/build/classes/native/macos/arm64/"
  
  # Create the demo JAR with all classes and resources
  COMMAND ${Java_JAR_EXECUTABLE} cfe "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-demo.jar"
          com.doomhowl.touchscrollphysics.TouchScrollerDemo
          -C "${CMAKE_CURRENT_SOURCE_DIR}/build/classes" .
  
  COMMENT "Compiling Java demo and creating JAR"
  VERBATIM
)

# Add dependency on the JNI library
add_dependencies(touch_scroll_physics_java_demo touch_scroll_physics_jni)

# Installation
install(FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/build/libs/touch-scroll-physics-demo.jar"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}) 