set(protoc_files
  ${protobuf_source_dir}/src/google/protobuf/compiler/main.cc
)

if (MSVC)
set(protoc_rc_files
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc
)
endif()

add_executable(protoc ${protoc_files} ${protoc_rc_files})
target_link_libraries(protoc libprotoc libprotobuf)
add_executable(protobuf::protoc ALIAS protoc)

set_target_properties(protoc PROPERTIES
    VERSION ${protobuf_VERSION})

add_custom_command(TARGET protoc 
	COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/src/proto/compile_proto.cmake
	VERBATIM
)

# include(${PROJECT_SOURCE_DIR}/src/proto/compile_proto.cmake)