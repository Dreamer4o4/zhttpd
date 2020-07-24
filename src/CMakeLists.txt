include_directories (${CMAKE_SOURCE_DIR}/src/base)

aux_source_directory (${CMAKE_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/test SRC_TEST)

add_executable (server ${SRC_TEST} ${SRC_BASE})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
