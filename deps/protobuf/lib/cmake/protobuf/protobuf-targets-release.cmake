#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "protobuf::protobuf-lite" for configuration "Release"
set_property(TARGET protobuf::protobuf-lite APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(protobuf::protobuf-lite PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libprotobuf-lite.so"
  IMPORTED_SONAME_RELEASE "libprotobuf-lite.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::protobuf-lite )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::protobuf-lite "${_IMPORT_PREFIX}/lib/libprotobuf-lite.so" )

# Import target "protobuf::protobuf" for configuration "Release"
set_property(TARGET protobuf::protobuf APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(protobuf::protobuf PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libprotobuf.so"
  IMPORTED_SONAME_RELEASE "libprotobuf.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::protobuf )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::protobuf "${_IMPORT_PREFIX}/lib/libprotobuf.so" )

# Import target "protobuf::protoc" for configuration "Release"
set_property(TARGET protobuf::protoc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(protobuf::protoc PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libprotoc.so"
  IMPORTED_SONAME_RELEASE "libprotoc.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::protoc )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::protoc "${_IMPORT_PREFIX}/lib/libprotoc.so" )

# Import target "protobuf::protocb" for configuration "Release"
set_property(TARGET protobuf::protocb APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(protobuf::protocb PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/protocb"
  )

list(APPEND _IMPORT_CHECK_TARGETS protobuf::protocb )
list(APPEND _IMPORT_CHECK_FILES_FOR_protobuf::protocb "${_IMPORT_PREFIX}/bin/protocb" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
