
PROJECT(JREADER)

# Should suffice?;
cmake_minimum_required(VERSION 3.12.0)

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Assume ROOTSYS was setup in the environment;
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

FIND_PACKAGE(ROOT 6.0.0 REQUIRED COMPONENTS RIO Tree Hist)
include(${ROOT_USE_FILE})

SET( CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -pthread -fPIC" )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(writer writer.cc)
target_link_libraries(writer ${ROOT_LIBRARIES})

add_executable(reader1 reader1.cc)
target_link_libraries(reader1 ${ROOT_LIBRARIES})

add_executable(reader2 reader2.cc)
target_link_libraries(reader2 ${ROOT_LIBRARIES})

add_executable(reader3 reader3.cc)
target_link_libraries(reader3 ${ROOT_LIBRARIES})

add_executable(reader4 reader4.cc)
target_link_libraries(reader4 ${ROOT_LIBRARIES} -lROOTDataFrame)

# -----------------------

set(INCLUDE_DIRECTORIES
${CMAKE_SOURCE_DIR}

${JANA}/src/lib
)
include_directories( ${INCLUDE_DIRECTORIES} )

SET(JREADER_LIB jreader)

set( JRSOURCES 
jreader.cc
JEventSource_jreader.cc
JEventProcessor_jreader.cc
)

ADD_LIBRARY( ${JREADER_LIB} SHARED ${JRSOURCES} )

TARGET_LINK_LIBRARIES(${JREADER_LIB} ${JANA}/lib/libJANA.a ${ROOT_LIBRARIES})
