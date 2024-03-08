cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
		easy_image.cc
		engine.cc
		ini_configuration.cc
		"2D L-Systemen/Line2D.h"
		"2D L-Systemen/Point2D.h"
		"2D L-Systemen/Color.h"
		l_parser.cc
		"2D L-Systemen/Color.cpp"
		"2D L-Systemen/LSystem2D.h"
		"2D L-Systemen/LSystem2D.cpp"
		TransformationMatrix.h
		"3D Lijntekeningen/vector3d.h"
		TransformationMatrix.cpp
		Figure.h
		Figure.cpp
		Face.cpp
		Projection.h
		Projection.cpp


)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION "utils ")
