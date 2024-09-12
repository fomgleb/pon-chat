cmake_minimum_required(VERSION 3.22)
project(
  pon-chat
  VERSION 0.1
  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding MinimalSocket library
include(FetchContent)
set(BUILD_MinimalCppSocket_SAMPLES
    OFF
    CACHE BOOL "" FORCE)
FetchContent_Declare(
  min_sock
  GIT_REPOSITORY https://github.com/andreacasalino/Minimal-Socket
  GIT_TAG v.3.1)
FetchContent_MakeAvailable(min_sock)

# Adding ftxui library
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0)
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_subdirectory(utils)
add_subdirectory(client)
add_subdirectory(server)
