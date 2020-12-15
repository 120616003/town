include_directories(inc)

file(GLOB_RECURSE server_SRC src/*.cpp)

add_library(server-massage SHARED ${server_SRC})

target_link_libraries(server-massage event)

install(TARGETS server-massage DESTINATION lib)