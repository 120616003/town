include_directories(includes)
include_directories(platform/inc)
include_directories(logic/inc)

file(GLOB_RECURSE database_SRC platform/src/*.cpp logic/src/*.cpp)

add_library(database-access SHARED ${database_SRC})

add_dependencies(database-access proto)

target_link_libraries(database-access mysqlpp mysqlclient proto)

install(TARGETS database-access DESTINATION lib)