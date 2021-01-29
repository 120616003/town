cmake_minimum_required (VERSION 3.10)

project (town)

SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/project) #安装到指定目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)   #设置可执行文件的输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)      #设置库文件的输出目录

if(Release)
    set(CMAKE_BUILD_TYPE Release)         # Release模式下的编译指令
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
else()
    set(CMAKE_BUILD_TYPE Debug)  # Debug模式下的编译指令
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
endif()

set(CMAKE_CXX_STANDARD 14)

# if(CONAN_LIBCXX STREQUAL "libstdc++11")
#     add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
# elseif(CONAN_LIBCXX STREQUAL "libstdc++")
#     add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
# endif()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  SET(CMAKE_CXX_COMPILER      "ccache")
  SET(CMAKE_CXX_COMPILER_ARG1 "/usr/bin/c++")
endif()

if(LOG STREQUAL "STDLOG")
  set(LOG_TYPE "STDLOG")
elseif(LOG STREQUAL "FILELOG")
  set(LOG_TYPE "FILELOG")
else()
  set(LOG_TYPE "STDLOG")
endif()

execute_process(COMMAND bash 
	${CMAKE_CURRENT_SOURCE_DIR}/src/proto/protofile/check/check_change.sh 
	${CMAKE_BINARY_DIR}/bin/protoc-3.14.0.0 
	${CMAKE_BINARY_DIR}/bin/protoc
	${CMAKE_CURRENT_SOURCE_DIR}/src/proto/protofile/)

# third_party include
set(protobuf_SOURCE_DIR ${PROJECT_SOURCE_DIR}/third_party/protobuf-3.14.0/cmake)
set(BUILD_SHARED_LIBS 1)
include_directories(${PROJECT_SOURCE_DIR}/third_party/protobuf-3.14.0/src/)
include_directories(${PROJECT_SOURCE_DIR}/third_party/spdlog-1.8.1/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party/rapidjson-1.1.0/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party/boost_1_75_0)
include_directories(/usr/include/mysql)

# core include
configure_file (${PROJECT_SOURCE_DIR}/town_config.h.in ${PROJECT_SOURCE_DIR}/src/common/town_config.h)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${PROJECT_SOURCE_DIR}/src/proto/inc)

# lib
add_subdirectory(third_party/protobuf-3.14.0/cmake)
add_subdirectory(src/proto)
add_subdirectory(src/database)
add_subdirectory(src/server)
add_subdirectory(src/main)