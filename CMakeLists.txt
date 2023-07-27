cmake_minimum_required(VERSION 3.14)

project(tboxhmi VERSION 2.0.2 LANGUAGES CXX)


add_subdirectory(${CMAKE_SOURCE_DIR}/third/three)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(COPY ${CONAN_PROJ_ROOT}/share/proj/proj.db DESTINATION ${CMAKE_BINARY_DIR}/bin)

# generate proto files
set(PROTO_SOURCE_DIR ${PROJECT_SOURCE_DIR}/service/proto)
message("CMAKE_BINARY_DIR ====" ${CMAKE_BINARY_DIR})
message("Copy proto to current dir and generate cc files from " ${CONAN_TBOXHMI-COMMON_ROOT}/proto)
execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/generate_proto.sh ${CMAKE_CURRENT_SOURCE_DIR} ${CONAN_TBOXHMI-COMMON_ROOT} ${CONAN_PROTOBUF_ROOT} ${PROTO_SOURCE_DIR}
    TIMEOUT 3
    RESULT_VARIABLE result_var
    OUTPUT_VARIABLE output_var
    ERROR_VARIABLE error_var
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE)

message(STATUS "result: ${result_var}")
message(STATUS "output: ${output_var}")
message(STATUS "have no error: ${error_var}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O0 -Wno-unused-variable -pthread")

option(PLATFORM_IMX8 "option for debug" OFF)
option(PLATFORM_X86 "option for x86" OFF)
option(PLATFORM_X64 "option for x64" ON)
option(PLATFORM_ARM64 "option for arm64" OFF)

if(PLATFORM_IMX8)
    add_definitions(-DPLATFORM_IMX8)
endif(PLATFORM_IMX8)

if(PLATFORM_X86)                           
    add_definitions(-DPLATFORM_X86)
endif(PLATFORM_X86)

if(PLATFORM_X64)
    add_definitions(-DPLATFORM_X64)
endif(PLATFORM_X64)

if(PLATFORM_ARM64)
    add_definitions(-DPLATFORM_ARM64)
endif(PLATFORM_ARM64)

# 增加版本信息
# 版本编译时间
string(TIMESTAMP COMPILE_TIME %Y/%m/%d-%H:%M:%S)
set(BUILD_TIME  ${COMPILE_TIME})
# 版本发布时间
string(TIMESTAMP COMPILE_TIME %Y/%m/%d)
set(PUBLISH_TIME  ${COMPILE_TIME})

# git 信息
include(./GitInfo.cmake)
# GIT_HASH
set(GIT_HASH "")
get_git_hash(GIT_HASH)
message(STATUS "Git hash is ${GIT_HASH}")
# git_BRANCh
set(GIT_BRANCH "")
get_git_branch(GIT_BRANCH)
message(STATUS "Git branch is ${GIT_BRANCH}")

add_definitions(-DHMI_BUILD_VERSION="${PROJECT_VERSION}")
add_definitions(-DHMI_BUILD_TIME="${BUILD_TIME}")

file(TOUCH ${PROJECT_SOURCE_DIR}/version)
file(WRITE ${PROJECT_SOURCE_DIR}/version "## 版本号")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n${PROJECT_VERSION}")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n## 发布时间")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n${PUBLISH_TIME}")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n## 分支")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n${GIT_BRANCH}")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n## CommitId")
file(APPEND ${PROJECT_SOURCE_DIR}/version "\n${GIT_HASH}")
file(COPY ${PROJECT_SOURCE_DIR}/version DESTINATION ${CMAKE_BINARY_DIR}/bin)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Widgets Multimedia WebEngine)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(SAU_HMI_INCLUDE ${PROJECT_SOURCE_DIR}/service/sau_client/library/x86/zmqex/include)
    set(SAU_HMI_LIB ${PROJECT_SOURCE_DIR}/service/sau_client/library/x86/zmqex/lib/libzmqex.so)
else()
    set(SAU_HMI_INCLUDE ${PROJECT_SOURCE_DIR}/service/sau_client/library/aarch64/zmqex/include)
    set(SAU_HMI_LIB ${PROJECT_SOURCE_DIR}/service/sau_client/library/aarch64/zmqex/lib/libzmqex.so)
endif()


include_directories(
    modeldata/include
    # tops
    ${PROJECT_SOURCE_DIR}/common
    ${PROJECT_SOURCE_DIR}/common/base
    ${PROJECT_SOURCE_DIR}/common/utils
    ${PROJECT_SOURCE_DIR}/common/coordinate_convert/src
    ${PROJECT_SOURCE_DIR}/common/leveldb
    ${PROJECT_SOURCE_DIR}/common/Cini
    ${PROJECT_SOURCE_DIR}/common/OpenGLManager
    ${PROJECT_SOURCE_DIR}/common/CTaskThreadManager
    ${PROJECT_SOURCE_DIR}/common/Semaphore
    ${PROJECT_SOURCE_DIR}/common/Network
    ${PROJECT_SOURCE_DIR}/common/Widgets
    ${PROJECT_SOURCE_DIR}/common/MapConfig
    ${PROJECT_SOURCE_DIR}/service/proto/can
    ${PROJECT_SOURCE_DIR}/service/proto/adu
    ${PROJECT_SOURCE_DIR}/service/proto/sau
    ${PROJECT_SOURCE_DIR}/service/svbox_client/proto
    # ${PROJECT_SOURCE_DIR}/sim-proto

    ${SAU_HMI_INCLUDE}
    ${PROJECT_SOURCE_DIR}/service/adu_client/src
    ${PROJECT_SOURCE_DIR}/service/adu_client/src/concurrent_quene
    ${PROJECT_SOURCE_DIR}/service/tbox_client

)

aux_source_directory(. MAIN_SRC)
message("source files from ./:" , ${MAIN_SRC})
# proto
aux_source_directory(${PROJECT_SOURCE_DIR}/service/proto/can CAN_PROTO_SRC)
message("source files from ./proto/can: ", ${CAN_PROTO_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/service/proto/adu ADU_PROTO_SRC)
message("source files from ./proto/adu: " , ${ADU_PROTO_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/service/proto/sau SAU_PROTO_SRC)
message("source files from ./proto/sau: " , ${SAU_PROTO_SRC})
# aux_source_directory(sim-proto SIM_PROTO_SRC)
# message("source files from ./sim-proto:" , ${SIM_PROTO_SRC})

# modeldata
aux_source_directory(modeldata/src/ MODEL_SRC)
message("source files from ./modeldata:" , ${MODEL_SRC})
# tops
# aux_source_directory(tops TOPS_SRC)
# message("source files from ./tops:" , ${TOPS_SRC})

# common
aux_source_directory(${PROJECT_SOURCE_DIR}/common COMMON_SRC)
message("source files from ./common:" , ${COMMON_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/coordinate_convert/src COORDINATE_CONVERT_SRC)
message("source files from ./common/coordinate_convert/src:" , ${COORDINATE_CONVERT_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/utils UTILS_SRC)
message("source files from ./common/utils:" , ${UTILS_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/Cini CINI_SRC)
message("source files from ./common/Cini:" , ${CINI_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/OpenGLManager OPENGLMANAGER_SRC)
message("source files from ./common/OpenGLManager:" , ${OPENGLMANAGER_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/CTaskThreadManager CTASKTHREADMANAGER_SRC)
message("source files from ./common/CTaskThreadManager:" , ${CTASKTHREADMANAGER_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/Semaphore SEMAPHORE_SRC)
message("source files from ./common/Semaphore:" , ${SEMAPHORE_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/Network NETWORK_SRC)
message("source files from ./common/Network:" , ${NETWORK_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/Widgets WIDGETS_SRC)
message("source files from ./common/Widgets:" , ${WIDGETS_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/common/MapConfig MAPCONFIG_SRC)
message("source files from ./common/MapConfig:" , ${MAPCONFIG_SRC})

# config
aux_source_directory(${PROJECT_SOURCE_DIR}/config CONFIG_SRC)
message("source files from ./config:" , ${CONFIG_SRC})
# leveldb
aux_source_directory(${PROJECT_SOURCE_DIR}/common/leveldb LEVELDB_SRC)
message("source files from ./common/leveldb:" , ${LEVELDB_SRC})

# service
# tbox client
aux_source_directory(${PROJECT_SOURCE_DIR}/service/tbox_client TBOX_CLIENT_SRC)
message("source files from ./tobx_client:" , ${TBOX_CLIENT_SRC})
# sau_client
aux_source_directory(${PROJECT_SOURCE_DIR}/service/sau_client SAU_CLIENT_SRC)
message("source files from ./sau_client:" , ${SAU_CLIENT_SRC})
# adu client
aux_source_directory(${PROJECT_SOURCE_DIR}/service/adu_client/src ADU_CLIENT_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/service/adu_client/src/concurrent_quene ADU_CLIENT_SRC)
message("source files from ./adu_client/src" , ${ADU_CLIENT_SRC})
# svbox clieant
aux_source_directory(${PROJECT_SOURCE_DIR}/service/svbox_client/proto SVBOX_PROTO_SRC)
message("source files from ./svbox_client/proto: " , ${SVBOX_PROTO_SRC})
aux_source_directory(${PROJECT_SOURCE_DIR}/service/svbox_client/reverse SVBOX_REVERSE_SRC)
message("source files from ./svbox_client/reverse:" , ${SVBOX_REVERSE_SRC})

# autodrive
aux_source_directory(autodrive AUTODRIVE_SRC)
message("source files from ./autodrive:" , ${AUTODRIVE_SRC})

add_subdirectory(${CMAKE_SOURCE_DIR}/features)

set(PROJECT_SOURCES
    qml.qrc
    ${MAIN_SRC}
    ${CAN_PROTO_SRC}
    ${ADU_PROTO_SRC}
    ${SAU_PROTO_SRC}
    ${SIM_PROTO_SRC}
    ${MODEL_SRC}
    ${TOPS_SRC}
    ${COMMON_SRC}
    ${COORDINATE_CONVERT_SRC}
    ${UTILS_SRC}
    ${CINI_SRC}
    ${OPENGLMANAGER_SRC}
    ${CTASKTHREADMANAGER_SRC}
    ${SEMAPHORE_SRC}
    ${CONFIG_SRC}
    ${LEVELDB_SRC}
    ${NETWORK_SRC}
    ${WIDGETS_SRC}
    ${MAPCONFIG_SRC}

    ${TBOX_CLIENT_SRC}
    ${SAU_CLIENT_SRC}
    ${ADU_CLIENT_SRC}
    ${SVBOX_PROTO_SRC}
    ${SVBOX_REVERSE_SRC}
    ${AUTODRIVE_SRC}
    ${FEATURES_SRC}
    ${FEATURES_HEADER}
)

add_subdirectory(${CMAKE_SOURCE_DIR}/service/adu_client)
add_subdirectory(${CMAKE_SOURCE_DIR}/common/coordinate_convert)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tboxhmi
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET DEMO APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tboxhmi SHARED
            ${PROJECT_SOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tboxhmi
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(tboxhmi
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(tboxhmi
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(tboxhmi PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(
    tboxhmi
    # PUBLIC coordinate_convert
    PRIVATE ${CMAKE_THREAD_LIBS_INIT}
    ${CONAN_LIBS}
    PRIVATE ${SAU_HMI_LIB}
    Qt5::Multimedia
    Qt5::WebEngine
    libprotobuf-lite.so
    libprotobuf.so
    assimp
    three
    features
    # hiredis
)

target_include_directories(tboxhmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/config)
target_include_directories(tboxhmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/service/svbox_client/reverse)
target_include_directories(tboxhmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/service/sau_client)
# target_include_directories(tboxhmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/coordinate_convert/src)
target_include_directories(tboxhmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/autodrive)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(tboxhmi)
    qt_finalize_executable(tboxhmi)
endif()

add_custom_target("resource" ALL  
  VERBATIM 
  COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/bin/resource/3d" 
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resource/3d"  "${PROJECT_BINARY_DIR}/bin/resource/3d" 
  COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/resource/3d/autodrive.ini"  "${PROJECT_BINARY_DIR}/bin" 
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resource/maps"  "${PROJECT_BINARY_DIR}/bin/resource/maps" 
)

add_custom_target("config" ALL  
  VERBATIM 
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/resource/config"  "${PROJECT_BINARY_DIR}/bin/config" 
)
