include_directories(includes)
include_directories(platform/inc)
include_directories(logic/inc)

file(GLOB_RECURSE server_SRC platform/src/*.cpp  logic/src/*.cpp)

add_library(server-massage SHARED ${server_SRC})

add_dependencies(server-massage proto)

target_link_libraries(server-massage event proto)

install(TARGETS server-massage DESTINATION lib)