# CMakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(AnaTreeLoop)
add_subdirectory(AnaTreeLoop)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/opt/root6/etc/root/cmake/)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
#find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
#include(${ROOT_USE_FILE})

#include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
#add_definitions(${ROOT_CXX_FLAGS})

#ROOT_GENERATE_DICTIONARY(G__AnaTreeLoop AnaTreeLoop/AnaTreeLoop.h AnaTreeLoop/AnaTreeLoopData.h AnaTreeLoop/AnaTreeTracks.h AnaTreeLoop/AnaTreeVertex.h AnaTreeLoop/AnaTreeAlgs.h AnaTreeLoop LINKDEF AnaTreeLoopLinkDef.h)

#---Create a shared library with geneated dictionary
#add_library(libAnaTreeLoop SHARED AnaTreeLoop.cxx G__AnaTreeLoop.cxx)
#target_link_libraries(libAnaTreeLoop ${ROOT_LIBRARIES}) 

#---Create  a main program using the library
#add_executable(Main MainEvent.cxx)
#target_link_libraries(Main Event)
