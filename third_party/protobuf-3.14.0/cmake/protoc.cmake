set(protoc_files
  ${protobuf_source_dir}/src/google/protobuf/compiler/main.cc
)

if (MSVC)
set(protoc_rc_files
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc
)
endif()

add_executable(protocb ${protoc_files} ${protoc_rc_files})
target_link_libraries(protocb protoc protobuf)
add_executable(protobuf::protocb ALIAS protocb)

# set_target_properties(protoc PROPERTIES
#     VERSION ${protobuf_VERSION})

add_custom_command(TARGET protocb 
	COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/src/proto/compile_proto.cmake
	VERBATIM
)