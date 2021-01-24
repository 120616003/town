include_directories(includes)
include_directories(platform/inc)
include_directories(logic/inc)

file(GLOB_RECURSE mysql_SRC platform/src/*.cpp logic/src/*.cpp)

add_library(mysql-access SHARED ${mysql_SRC})

target_link_libraries(mysql-access mysqlpp mysqlclient)

install(TARGETS mysql-access DESTINATION lib)