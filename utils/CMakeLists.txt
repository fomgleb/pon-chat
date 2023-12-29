set(SRC_DIR src)
set(INC_DIR ..)

file(GLOB SOURCES "${SRC_DIR}/*.cc")
add_library(utils_lib STATIC ${SOURCES})
target_link_libraries(utils_lib MinimalSocket)
target_include_directories(utils_lib PUBLIC ${INC_DIR} ${min_sock_SOURCE_DIR}/src/header)
