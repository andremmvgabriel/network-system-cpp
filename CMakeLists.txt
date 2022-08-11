cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(NetworkSystem)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Changes the binary, static lib, and libraries default paths of the CMake build, respectively
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

INCLUDE_DIRECTORIES ( include )

set( src_network_system_lib
)
add_library( NetworkSystem STATIC ${src_network_system_lib} )
target_link_libraries( NetworkSystem
    zmq
)
