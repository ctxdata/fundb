
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(FunDB VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_BUILD_TYPE "Debug")

# CTest
enable_testing()

# gmock gtest https://crascit.com/2015/07/25/cmake-gtest/
#configure_file("${PROJECT_SOURCE_DIR}/build-deps/gtest_CMakeLists.txt.in" googletest-download/CMakeLists.txt)
#execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
#        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
#execute_process(COMMAND "${CMAKE_COMMAND}" --build .
#        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # don't override our compiler/linker options when building gtest
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src" "${CMAKE_BINARY_DIR}/googletest-build")

# Output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes.
set(FUNDB_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)
set(FUNDB_TEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/include)
set(FUNDB_THIRD_PARTY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party)
include_directories(${FUNDB_SRC_INCLUDE_DIR} ${FUNDB_TEST_INCLUDE_DIR} ${FUNDB_THIRD_PARTY_INCLUDE_DIR})
include_directories(BEFORE src) # This is needed for gtest.

add_subdirectory(src)
add_subdirectory(test)