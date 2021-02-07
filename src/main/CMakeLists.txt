include_directories(${PROJECT_SOURCE_DIR}/src/database/includes)
include_directories(${PROJECT_SOURCE_DIR}/src/database/logic/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/database/platform/inc)

include_directories(${PROJECT_SOURCE_DIR}/src/server/includes)
include_directories(${PROJECT_SOURCE_DIR}/src/server/logic/inc)
include_directories(${PROJECT_SOURCE_DIR}/src/server/platform/inc)

file(GLOB_RECURSE main_SRC main.cpp)

add_executable(main ${main_SRC})

target_link_libraries(main 
	server-massage event
	database-access mysqlpp mysqlclient
	proto
	jsoncpp)

install(TARGETS main DESTINATION bin)