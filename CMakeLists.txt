######################################################################
## CMakeLists.txt --- gsCInterface
## This file is part of the G+Smo library.
##
######################################################################

project(gsCInterface LANGUAGES CXX)

# Apply G+Smo config
include(gsConfig)

## Collect files
aux_header_directory(${CMAKE_CURRENT_SOURCE_DIR}/src ${PROJECT_NAME}_H)
aux_cpp_directory   (${CMAKE_CURRENT_SOURCE_DIR}/src ${PROJECT_NAME}_CPP)

if( (NOT GISMO_BUILD_LIB) )
  aux_instance_directory (${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_NAME}_INS)
  if(${PROJECT_NAME}_INS)
    LIST( REMOVE_ITEM ${PROJECT_NAME}_CPP ${${PROJECT_NAME}_INS})
  endif()
endif()

# Compile statically the extension
add_library(${PROJECT_NAME} OBJECT
  ${${PROJECT_NAME}_H}
  ${${PROJECT_NAME}_CPP})

set_target_properties(${PROJECT_NAME} PROPERTIES
  COMPILE_DEFINITIONS gismo_EXPORTS
  POSITION_INDEPENDENT_CODE ON
  #LINKER_LANGUAGE C
  FOLDER "G+Smo modules" )

set(gismo_MODULES ${gismo_MODULES} $<TARGET_OBJECTS:${PROJECT_NAME}>
  CACHE INTERNAL "G+Smo modules" )

#Symlink include dir (in case your headers are in /src)
execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  DESTINATION "include/gismo/${PROJECT_NAME}"
  FILES_MATCHING PATTERN "*.h" )

add_gismo_executable(${CMAKE_CURRENT_SOURCE_DIR}/examples/basis_cexample.c)
add_gismo_executable(${CMAKE_CURRENT_SOURCE_DIR}/examples/geometry_cexample.c)

add_custom_target(C_plugins)

# Add submodules to Cgismo.h
set(gsOptional_includes "")
foreach(gssm ${GISMO_OPTIONAL})
  string(STRIP ${gssm} SUBMODULE)
  if (EXISTS "${gismo_SOURCE_DIR}/optional/${SUBMODULE}/src/cinterface")
    set(gsOptional_includes "${gsOptional_includes}#ifdef ${SUBMODULE}_ENABLED")
    # Loop over the header files in the submodule
    file( GLOB SUBMODULE_HEADERS ${gismo_SOURCE_DIR}/optional/${SUBMODULE}/src/cinterface/*.h)
    foreach(HEADER ${SUBMODULE_HEADERS})
      get_filename_component(HEADER_NAME ${HEADER} NAME)
      set(gsOptional_includes "${gsOptional_includes}\n#include <${SUBMODULE}/cinterface/${HEADER_NAME}>")
    endforeach()
    set(gsOptional_includes "${gsOptional_includes}\n#endif\n")
  endif()
endforeach()
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/Cgismo.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/Cgismo.h")
