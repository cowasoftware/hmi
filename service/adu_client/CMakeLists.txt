#find_package(Protobuf  REQUIRED)
find_package(Threads REQUIRED)

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../proto/adu)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../proto/adu PROTO_SRC)
# set(PROTO_SRC ${PROTO_SRC} )
# message(STATUS "client sources list: ${PROTO_SRC}")

#add_subdirectory(proto)
add_subdirectory(example)

# include_directories(./3rd/jsoncpp/include)
# link_directories(/home/cowa/tboxhmi/adu_client/3rd/jsoncpp/lib)
# include_directories(./3rd/libzmq/include)
# link_directories(/home/cowa/tboxhmi/adu_client/3rd/libzmq/lib)

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CLIENT_SRC)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/proto/out CLIENT_SRC)

# set(CLIENT_SRC ${CLIENT_SRC} ${PROTO_SRC} )
# message(STATUS "client sources list: ${CLIENT_SRC}")
# add_library(proxy_client ${CLIENT_SRC} )
# target_link_libraries(proxy_client PUBLIC zmq protobuf pthread jsoncpp)
# target_include_directories(proxy_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/proto/out)

file(COPY ./hmi_client_config.json DESTINATION ${CMAKE_BINARY_DIR}/bin)
