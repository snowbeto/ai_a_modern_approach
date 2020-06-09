cmake_minimum_required(VERSION 2.8)

project(AI)

set(CMAKE_CXX_FLAGS "-std=c++0x")

set(CMAKE_BUILD_TYPE Debug)

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)


set (source "${CMAKE_SOURCE_DIR}/maps")
set (destination "${EXECUTABLE_OUTPUT_PATH}/maps")

add_custom_target(copy-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/maps
    ${EXECUTABLE_OUTPUT_PATH}/maps
    )


include_directories (
    include
)

add_executable( bfs_vs_dfs 
		src/main.cpp
		src/agent.cpp
		src/environment.cpp )

