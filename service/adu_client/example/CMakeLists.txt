
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../sim-proto)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../proto/adu)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} EXAMPLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../src EXAMPLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../src/concurrent_quene EXAMPLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../../proto/adu EXAMPLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../../svbox_client/proto EXAMPLE_SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../../../common/coordinate_convert/src EXAMPLE_SRC)

set(EXAMPLE_SRC ${EXAMPLE_SRC} ${PROTO_SRC} )
message(STATUS "client sources list: ${EXAMPLE_SRC}")

set(INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/../src/")
set(INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/../src/concurrent_quene" ${INCLUDE_DIRS})
set(INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/../../../common/coordinate_convert/src" ${INCLUDE_DIRS})
# set(INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/../../../sim-proto" ${INCLUDE_DIRS})
set(INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/../../proto/adu" ${INCLUDE_DIRS})
message(STATUS "client include list: ${INCLUDE_DIRS}")

add_executable(proxy_client ${EXAMPLE_SRC} )
target_include_directories(proxy_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../common/coordinate_convert/src ${CMAKE_CURRENT_SOURCE_DIR}/../src/  
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/concurrent_quene
     ${CMAKE_CURRENT_SOURCE_DIR}/../../proto/adu
     )
target_link_libraries(proxy_client PUBLIC zmq protobuf pthread jsoncpp proj)


