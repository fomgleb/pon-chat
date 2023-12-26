set(SRC_DIR src)
set(INC_DIR ..)

file(GLOB SOURCES "${SRC_DIR}/*.cpp")
add_executable(server_main ${SOURCES})
target_include_directories(server_main PUBLIC ${INC_DIR})
