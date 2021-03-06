function(printList items)
  foreach (item ${items})
    message("\t ${item}")
  endforeach()
endfunction()

get_property(COMPILER_OPTIONS     DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY COMPILE_OPTIONS)
get_property(LINKER_OPTIONS       DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY LINK_OPTIONS)

message( STATUS "------------------------------------------------------------------" )
message( STATUS "HOST System Name:  ${CMAKE_HOST_SYSTEM_NAME}" )
message( STATUS "HOST System:       ${CMAKE_HOST_SYSTEM}" )
message( STATUS "CMake Generator:   ${CMAKE_GENERATOR}" )
message( STATUS "CMAKE_BUILD_TYPE:  ${CMAKE_BUILD_TYPE}" )
message( STATUS "Compiler info: ${CMAKE_CXX_COMPILER_ID} (${CMAKE_CXX_COMPILER}) ; version: ${CMAKE_CXX_COMPILER_VERSION}")
message( STATUS "PLATFORM_FLAG: ${PLATFORM_FLAG}")
message( STATUS " --- Compiler flags --- ")
message( STATUS "General:           ${CMAKE_CXX_FLAGS}" )
printList("${COMPILER_OPTIONS}")
message( STATUS "Debug:             ${CMAKE_CXX_FLAGS_DEBUG}" )
message( STATUS "Release:           ${CMAKE_CXX_FLAGS_RELEASE}" )
message( STATUS "RelWithDebInfo:    ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}" )
message( STATUS "MinSizeRel:        ${CMAKE_CXX_FLAGS_MINSIZEREL}" )
message( STATUS " --- Linker flags --- ")
message( STATUS "General:           ${CMAKE_EXE_LINKER_FLAGS}" )
printList("${LINKER_OPTIONS}")
message( STATUS "Debug:             ${CMAKE_EXE_LINKER_FLAGS_DEBUG}" )
message( STATUS "Release:           ${CMAKE_EXE_LINKER_FLAGS_RELEASE}" )
message( STATUS "RelWithDebInfo:    ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}" )
message( STATUS "MinSizeRel:        ${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL}" )
message( STATUS "" )
message( STATUS " --- Global CMake Options --- ")
message( STATUS "BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}" )
message( STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}" )
message( STATUS "" )
message( STATUS "" )

