cmake_minimum_required(VERSION 3.5)
project(TouchScrollPhysicsRoot C)
add_subdirectory(library)

if (DEFINED TSCROLL_BUILD_DEMOS)
  if (NOT MSVC)
    add_compile_options("-Wall" "-Wpedantic")
  endif()

  if (DEFINED TSCROLL_DOWNLOAD_RAYLIB)
    # Adding Raylib
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
    set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
      raylib
      GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
      GIT_TAG "master"
      GIT_PROGRESS TRUE
      GIT_SHALLOW 1
    )

    FetchContent_MakeAvailable(raylib)
  endif()
  
  add_subdirectory(demo)
endif()
