include_directories(src)

file(GLOB_RECURSE proto_SRC src/*.cc)

add_library(proto SHARED ${proto_SRC})

add_dependencies(proto libprotobuf)

target_link_libraries(proto libprotobuf)

install(TARGETS proto DESTINATION lib)