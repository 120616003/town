include_directories(include)

file(GLOB_RECURSE main_SRC main.cpp)

add_executable(main ${main_SRC})

target_link_libraries(main mysql-access mysqlclient)

install(TARGETS main DESTINATION bin)