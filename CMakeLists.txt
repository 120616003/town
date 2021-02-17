cmake_minimum_required (VERSION 3.10)

project (town)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/project) #安装到指定目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)   #设置可执行文件的输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)      #设置库文件的输出目录

# set(Release 1)

if(Release)
    set(CMAKE_BUILD_TYPE Release) # Release模式下的编译指令
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
else()
    set(CMAKE_BUILD_TYPE Debug)   # Debug模式下的编译指令
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
endif()

set(CMAKE_CXX_STANDARD 14)
# add_definitions(-D_GLIBCXX_USE_CXX14_ABI=1)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER      "ccache")
    set(CMAKE_CXX_COMPILER_ARG1 "g++")
endif()

if(LOG STREQUAL "STDLOG")
    set(LOG_TYPE "STDLOG")
elseif(LOG STREQUAL "FILELOG")
    set(LOG_TYPE "FILELOG")
else()
    set(LOG_TYPE "STDLOG")
endif()

# third_party include
include_directories(${PROJECT_SOURCE_DIR}/deps/protobuf/include/)
include_directories(${PROJECT_SOURCE_DIR}/deps/protobuf/protofile/)
include_directories(${PROJECT_SOURCE_DIR}/third_party/spdlog-1.8.1/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party/boost_1_75_0)
include_directories(/usr/include/mysql)

# third_party lib
link_directories(${PROJECT_SOURCE_DIR}/deps/protobuf/lib/)

# core include
configure_file (${PROJECT_SOURCE_DIR}/town_config.h.in ${PROJECT_SOURCE_DIR}/src/common/town_config.h)
include_directories(${PROJECT_SOURCE_DIR}/src/common)

# lib
if(COMPILE STREQUAL "proto")
    set(protobuf_SOURCE_DIR ${PROJECT_SOURCE_DIR}/third_party/protobuf-3.14.0/cmake)
    set(BUILD_SHARED_LIBS 1)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/deps/protobuf) #安装到指定目录
    add_subdirectory(third_party/protobuf-3.14.0/cmake)
else()
    execute_process(COMMAND bash protofile/compile_protobuf.sh bin WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/deps/protobuf/)
    add_subdirectory(deps/protobuf/)
    add_subdirectory(src/database)
    add_subdirectory(src/server)
    add_subdirectory(src/main)

    execute_process(COMMAND ln -fs ${PROJECT_SOURCE_DIR}/src/config ${PROJECT_BINARY_DIR}/)
    execute_process(COMMAND mkdir ${PROJECT_BINARY_DIR}/bin/)
    execute_process(COMMAND ln -fs ${PROJECT_SOURCE_DIR}/src/config ${PROJECT_BINARY_DIR}/bin/)
endif()