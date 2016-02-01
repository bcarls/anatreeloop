# get all the *.cxx filenames, to compile them into a lib
file(GLOB SOME_PROJ_LIB_SRCS "${PROJECT_SOURCE_DIR}/AnaTreeLoop/*.cxx")
# include ROOT library and include files
include_directories($ENV{ROOTINCLUDE})
link_directories($ENV{ROOTLIB})

include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_CXX_FLAGS})

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTCMAKE})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})
ROOT_GENERATE_DICTIONARY(G__AnaTreeLoop AnaTreeLoop/AnaTreeLoopClusterLinearity.h AnaTreeLoop/AnaTreeLoopWireVariation.h AnaTreeLoop/AnaTreeLoop.h AnaTreeLoop/AnaTreeLoopData.h AnaTreeLoop/AnaTreeTracks.h AnaTreeLoop/AnaTreeClusters.h AnaTreeLoop/AnaTreeVertex.h AnaTreeLoop/AnaTreeHits.h AnaTreeLoop/AnaTreeRunInfo.h AnaTreeLoop/AnaTreeAlgs.h LINKDEF AnaTreeLoop/AnaTreeLoopLinkDef.h)

# and compile src into a library
add_library(AnaTreeLoop SHARED ${SOME_PROJ_LIB_SRCS} G__AnaTreeLoop.cxx)
target_compile_features(AnaTreeLoop PRIVATE cxx_range_for)
# here, list the ROOT libraries you require
target_link_libraries(AnaTreeLoop dl Core RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread Gui pthread m) 
