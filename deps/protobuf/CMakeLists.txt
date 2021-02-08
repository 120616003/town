file(GLOB_RECURSE proto_SRC protofile/*.cc protofile/*.proto)

add_library(proto SHARED ${proto_SRC})

set_target_properties(proto PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(proto protobuf)

install(TARGETS proto DESTINATION lib)