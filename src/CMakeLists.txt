cmake_minimum_required(VERSION 2.8.11)

# Create new project
project (libFingerPrint)

# Create variable containing all the CXX sources

set(
	SOURCES
	files/blur.cpp
	files/starter_1.cpp
	files/main_1.cpp
	files/starter3.cpp
	files/starter2.cpp
)

set(
	HEADERS
	headers/blur.h
	headers/starter_1.h
	headers/main_1.h
	headers/starter3.h
	headers/starter2.h
)

# Add all the sources to the project
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
include_directories("headers")
