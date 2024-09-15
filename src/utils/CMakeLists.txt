set(LIB_NAME "utils_lib")
set(SOURCE_DIR "src")
set(PRIVATE_HEADER_DIR "src")
set(PUBLIC_HEADER_DIR "include")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cc")

add_library(${LIB_NAME} STATIC ${SOURCES})

target_include_directories(
  ${LIB_NAME}
  PUBLIC ${PUBLIC_HEADER_DIR}
  PRIVATE ${PRIVATE_HEADER_DIR} ${min_sock_SOURCE_DIR}/src/header
          ${ftxui_SOURCE_DIR}/include)

target_link_libraries(${LIB_NAME} PRIVATE MinimalSocket)

target_include_directories(utils_lib PUBLIC ${INC_DIR}
                                            ${min_sock_SOURCE_DIR}/src/header)
