cmake_minimum_required(VERSION 3.3)
project(AnnoModdingTool)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

# First for the generic no-config case (e.g. with mingw)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(SCRS
	src/main.cpp
	src/ModelConverters.hpp src/ModelConverters.cpp
	src/ModelConverters/RpmConverter.hpp src/ModelConverters/RpmConverter.cpp
	src/ModelConverters/ColladaConverter.hpp src/ModelConverters/ColladaConverter.cpp
)

add_executable(${PROJECT_NAME} ${SCRS})
