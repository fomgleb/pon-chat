set(SRC_DIR src)
set(INC_DIR ..)

file(GLOB SOURCES "${SRC_DIR}/*.cc")
add_executable(client_main ${SOURCES})
target_link_libraries(client_main MinimalSocket utils_lib ftxui::screen
                      ftxui::dom ftxui::component)
target_include_directories(
  client_main PUBLIC ${INC_DIR} ${min_sock_SOURCE_DIR}/src/header
                     ${ftxui_SOURCE_DIR}/include)
