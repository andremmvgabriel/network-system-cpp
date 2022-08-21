cmake_minimum_required(VERSION 3.10)

# Set the project name (and version?)
project(Networking)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Changes the binary, static lib, and libraries default paths of the CMake build, respectively
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

# Dependencies
find_package( cppzmq REQUIRED )

INCLUDE_DIRECTORIES ( include )

set( src_networking_lib
    src/gabe/networking/networking.cpp

    src/gabe/networking/core/NetworkManager.cpp

    src/gabe/networking/utils/Communication.cpp
)
add_library( networking STATIC ${src_networking_lib} )
target_link_libraries( networking cppzmq )


add_subdirectory( tests )