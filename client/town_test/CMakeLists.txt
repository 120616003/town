cmake_minimum_required (VERSION 2.6)

project (town-client)

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

include_directories(${PROJECT_SOURCE_DIR}/../third_party/boost_1_75_0)
include_directories(${PROJECT_SOURCE_DIR}/../third_party/protobuf-3.14.0/src/)
include_directories(${PROJECT_SOURCE_DIR}/../src/common)
include_directories(${PROJECT_SOURCE_DIR}/../src/proto/src)
link_directories(${PROJECT_SOURCE_DIR}/../build/lib/)

add_subdirectory(src/test)