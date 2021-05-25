cmake_minimum_required(VERSION 3.5)

project(XY-Table LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( project_sources
   main.cpp
   positionmapper.h
   positionmapper.cpp
   xycontrol.h
   WiringPiSim.h
)

add_executable(XY-Table ${project_sources})
