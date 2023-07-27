cmake_minimum_required(VERSION 3.15.3)
project(cppgl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${PROJECT_SOURCE_DIR}/src PROJECT_SOURCES)
add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
