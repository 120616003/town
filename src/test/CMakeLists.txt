include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mysql/platform/inc)

message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/../mysql/platform/inc)

file(GLOB_RECURSE main_SRC main.cpp)

add_executable(main ${main_SRC})

target_link_libraries(main 
	server-massage event proto 
	mysql-access mysqlpp mysqlclient)

install(TARGETS main DESTINATION bin)