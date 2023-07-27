cmake_minimum_required(VERSION 3.14)
project(features)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Widgets Multimedia WebEngine Gui Qml)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB PROJECT_HEADER 
    ${PROJECT_SOURCE_DIR}/application/*.h
    ${PROJECT_SOURCE_DIR}/realtime_route/*.h
)

aux_source_directory(${PROJECT_SOURCE_DIR}/application  PROJECT_SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/realtime_route  PROJECT_SOURCES)
add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_RESOURCE} ${PROJECT_HEADER})
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/application
    ${PROJECT_SOURCE_DIR}/realtime_route
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick Qt5::Widgets Qt5::Multimedia Qt5::WebEngine Qt5::Gui Qt5::Qml)

# add_custom_target("config" ALL  
#   VERBATIM 
#   COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resource/config"  "${PROJECT_BINARY_DIR}/bin/config" 
# )

