file(GLOB_RECURSE fundb_sources ${PROJECT_SOURCE_DIR}/src/*/*.cpp ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp)
add_executable(fundb fundb.cpp ${fundb_sources}) 
add_library(fundb_shared SHARED ${fundb_sources})