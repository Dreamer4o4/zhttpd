include_directories (${CMAKE_SOURCE_DIR}/src/base)
include_directories (${CMAKE_SOURCE_DIR}/src/http)
include_directories (${CMAKE_SOURCE_DIR}/src/redis)

aux_source_directory (${CMAKE_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/http SRC_HTTP)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/redis SRC_REDIS)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/test SRC_TEST)

add_executable (server ${SRC_TEST} ${SRC_BASE} ${SRC_HTTP} ${SRC_REDIS})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
