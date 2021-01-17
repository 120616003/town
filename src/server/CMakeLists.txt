include_directories(inc)
include_directories(business_logic/inc)

file(GLOB_RECURSE server_SRC src/*.cpp business_logic/src/*.cpp)

add_library(server-massage SHARED ${server_SRC})

add_dependencies(server-massage proto)

target_link_libraries(server-massage event proto)

install(TARGETS server-massage DESTINATION lib)