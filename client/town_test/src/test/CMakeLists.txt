include_directories(inc)

add_executable(main src/client_main.cpp)

target_link_libraries(main event proto protobuf-lite protobuf)

install(TARGETS main DESTINATION bin)