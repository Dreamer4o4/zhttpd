include_directories (${CMAKE_SOURCE_DIR}/src/base)
include_directories (${CMAKE_SOURCE_DIR}/src/http)
include_directories (${CMAKE_SOURCE_DIR}/src/database)

aux_source_directory (${CMAKE_SOURCE_DIR}/src/base SRC_BASE)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/http SRC_HTTP)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/database SRC_DB)
aux_source_directory (${CMAKE_SOURCE_DIR}/src/blogserver SRC_BLOG)

add_executable (blogserver ${SRC_BLOG} ${SRC_BASE} ${SRC_HTTP} ${SRC_DB})

target_link_libraries(blogserver hiredis)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
