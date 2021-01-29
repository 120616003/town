execute_process(COMMAND -P rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/inc/* ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/src/*)

execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../../../build/bin/protoc --proto_path=${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/protofile/ --cpp_out=${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/src user.proto)

execute_process(COMMAND -P mv ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/src/*.h ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/inc)

# execute_process(COMMAND echo ${CMAKE_CURRENT_SOURCE_DIR})
# execute_process(COMMAND echo ${CMAKE_SOURCE_DIR})
# execute_process(COMMAND echo ${CMAKE_CURRRENT_BINARY_DIR})
# execute_process(COMMAND echo ${CMAKE_CURRENT_LIST_FILE})
# execute_process(COMMAND echo ${EXECUTABLE_OUTPUT_PATH})
# execute_process(COMMAND echo ${CMAKE_BINARY_DIR})
# execute_process(COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/protofile/check/protobuf.sh)