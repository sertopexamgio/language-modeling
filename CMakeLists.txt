cmake_minimum_required(VERSION 2.8)

project(asr)

# Using c++ 14
set(CMAKE_CXX_STANDARD 14)

set(SRC_PATH src)
set(${PROJECT_NAME}_SRC ${SRC_PATH}/main.cc)

set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake
	${CMAKE_CURRENT_SOURCE_DIR}/src/lm
)


#########################################################
# Executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )

# location of header files
include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/src"
)

include(lm)

link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
