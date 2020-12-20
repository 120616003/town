include_directories(include)

file(GLOB_RECURSE main_SRC main.cpp)

add_executable(main ${main_SRC})

# target_link_libraries(main mysql-access mysqlclient server-massage event proto libprotobuf)
target_link_libraries(main mysql-access server-massage event proto)

install(TARGETS main DESTINATION bin)