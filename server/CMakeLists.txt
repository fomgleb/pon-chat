set(SRC_DIR src)
set(INC_DIR ..)

file(GLOB SOURCES "${SRC_DIR}/*.cpp")
add_executable(server_main ${SOURCES})
target_link_libraries(server_main MinimalSocket)
target_include_directories(server_main PUBLIC ${INC_DIR} ${min_sock_SOURCE_DIR}/src/header)
