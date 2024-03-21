cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
    easy_image.cc
    engine.cc
    ini_configuration.cc
    l_parser.cc
    2D_L-Systemen/Color.cpp
    2D_L-Systemen/LSystem2D.cpp
    TransformationMatrix.cpp
    Figure.cpp
    Face.cpp
    Projection.cpp
    WireframeParser.cpp
    vector3d.cc
        FigureParser.h
        FigureParser.cpp
        ImageSize.h
        ImageSize.cpp
        Scale.h
        Scale.cpp
        2D_L-Systemen/Line2D.cpp
        Triangles.h
        Triangles.cpp
        Platonic.h
        NotPlatonic.h
        Platonic.cpp
        NotPlatonic.cpp

    Include.hpp
        l_SystemsFunc.h
        l_SystemsFunc.cpp)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable(${exe_name} ${engine_sources})
install(TARGETS ${exe_name} DESTINATION "utils ")
