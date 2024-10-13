cmake_minimum_required(VERSION 3.25)
project(
  pon-chat
  VERSION 0.1
  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding project_warning target
add_library(project_warnings INTERFACE)
target_compile_options(
  project_warnings
  INTERFACE -pedantic
            -Wall
            -Wextra
            -Wcast-align
            -Wcast-qual
            -Wctor-dtor-privacy
            -Wdisabled-optimization
            -Wformat=2
            -Winit-self
            -Wmissing-declarations
            -Wmissing-include-dirs
            -Wnoexcept
            -Wold-style-cast
            -Woverloaded-virtual
            -Wredundant-decls
            -Wshadow
            -Wsign-conversion
            -Wsign-promo
            -Wstrict-null-sentinel
            -Wstrict-overflow=5
            -Wswitch-default
            -Wundef
            -Werror
            -Wno-unused)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(
    project_warnings INTERFACE -Wmisleading-indentation -Wduplicated-cond
                               -Wlogical-op -Wuseless-cast)
  # target_link_libraries(project_options INTERFACE stdc++fs)
endif()

add_subdirectory(libs)
add_subdirectory(src)
