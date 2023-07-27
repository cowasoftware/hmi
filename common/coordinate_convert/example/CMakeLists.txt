aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../src EXAMPLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} EXAMPLE_SRC)

add_executable(coordinate_convert_example ${EXAMPLE_SRC})
target_include_directories(coordinate_convert_example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_link_libraries(coordinate_convert_example PRIVATE proj)