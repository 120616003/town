include_directories(src)

file(GLOB_RECURSE proto_SRC src/*.cc protofile/*.proto)

add_library(proto SHARED ${proto_SRC})

add_dependencies(proto libprotobuf protoc)

target_link_libraries(proto libprotobuf)

install(TARGETS proto DESTINATION lib)