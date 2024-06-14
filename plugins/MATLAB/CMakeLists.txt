######################################################################
## CMakeLists.txt --- Gismo.m
## This file is part of the G+Smo library.
##
######################################################################

project( Gismo.m )

#to do
#find_package(Matlab)

# Fetch all .cpp files to be mex'ed, and loop over these to set up
# mex-targets.
file( GLOB JL_SRCS src/gsCore/*.m)
file( GLOB JL_SRCS src/gsHSplines/*.m)
file( GLOB JL_SRCS src/gsMatrix/*.m)
file( GLOB JL_SRCS src/gsNurbs/*.m)

add_custom_target(${PROJECT_NAME} ALL DEPENDS gismo ${JL_OUTS})
      
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Gismo/src/Gismo_path.m.in" "${CMAKE_CURRENT_SOURCE_DIR}/Gismo/src/Gismo_path.m")

#INSTALL ...

