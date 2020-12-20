include_directories(inc)

add_executable(main src/client_main.cpp)

add_dependencies(main libprotobuf libprotobuf-lite)

target_link_libraries(main event proto libprotobuf-lite libprotobuf)

install(TARGETS main DESTINATION bin)