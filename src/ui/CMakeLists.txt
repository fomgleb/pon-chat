set(LIB_NAME "ui_lib")
set(SOURCE_DIR "src")
set(PRIVATE_HEADER_DIR "src")
set(PUBLIC_HEADER_DIR "include")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cc")

add_library(${LIB_NAME} STATIC ${SOURCES})

target_include_directories(
  ${LIB_NAME}
  PUBLIC ${PUBLIC_HEADER_DIR}
  PRIVATE ${PRIVATE_HEADER_DIR})

target_link_libraries(${LIB_NAME} PUBLIC protocols_lib ftxui::screen ftxui::dom
                                         ftxui::component events_lib)
