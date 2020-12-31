cmake_minimum_required (VERSION 3.10)

project (town)

SET(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/project) #安装到指定目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)   #设置可执行文件的输出目录
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)      #设置库文件的输出目录

if(Release)
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")         # Release模式下的编译指令
else()
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")  # Debug模式下的编译指令
endif()

set(CXX_FLAGS -std=c++17)


if(LOG STREQUAL "STDLOG")
  set(LOG_TYPE "STDLOG")
elseif(LOG STREQUAL "FILELOG")
  set(LOG_TYPE "FILELOG")
else()
  set(LOG_TYPE "STDLOG")
endif()

#third_party
set(protobuf_SOURCE_DIR ${PROJECT_SOURCE_DIR}/third_party/protobuf-3.14.0/cmake)
set(BUILD_SHARED_LIBS 1)
include_directories(${PROJECT_SOURCE_DIR}/third_party/protobuf-3.14.0/src/)
include_directories(${PROJECT_SOURCE_DIR}/third_party/spdlog-1.8.1/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party/rapidjson-1.1.0/include)
include_directories(${PROJECT_SOURCE_DIR}/third_party/boost_1_75_0)

#core
configure_file (${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/src/common/config.h)
include_directories(${PROJECT_SOURCE_DIR}/src/includes)
include_directories(${PROJECT_SOURCE_DIR}/src/server/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/common)
include_directories(${PROJECT_SOURCE_DIR}/src/proto/src)

#lib
add_subdirectory(third_party/protobuf-3.14.0/cmake)
add_subdirectory(src/proto)
add_subdirectory(src/mysql)
add_subdirectory(src/server)
add_subdirectory(src/test)