set(APP_NAME "client_app")
set(SOURCE_DIR "src")
set(PRIVATE_HEADER_DIR "src")
set(PUBLIC_HEADER_DIR "include")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cc")

add_executable(${APP_NAME} ${SOURCES})

target_include_directories(
  ${APP_NAME}
  PUBLIC ${PUBLIC_HEADER_DIR}
  PRIVATE ${PRIVATE_HEADER_DIR})

target_link_libraries(${APP_NAME} PRIVATE project_warnings ui_lib MinimalSocket
                                          console_input_lib)
