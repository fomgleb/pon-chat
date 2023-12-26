set(SRC_DIR src)
set(INC_DIR ..)

file(GLOB SOURCES "${SRC_DIR}/*.cpp")
add_executable(client_main ${SOURCES})
target_link_libraries(client_main MinimalSocket)
target_include_directories(client_main PUBLIC ${INC_DIR} ${min_sock_SOURCE_DIR}/src/header)
