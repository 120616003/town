include_directories(include)

file(GLOB_RECURSE mysql_SRC src/*.cpp)

add_library(mysql-access SHARED ${mysql_SRC})

target_link_libraries(mysql-access mysqlclient)

install(TARGETS mysql-access DESTINATION lib)