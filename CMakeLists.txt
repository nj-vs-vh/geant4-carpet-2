# See tutorial:
# https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/GettingStarted/makeFile.html#using-cmake-to-build-applications

# (1) CMake versions stuff
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
project(Carpet2)

# (2) GEANT4 package
find_package(Geant4 REQUIRED)

# (3) Include libraries
if(NOT DEFINED ENV{COAST_DIR})
    message( FATAL_ERROR "COAST_DIR environment variable must be set!" )
endif()

include(${Geant4_USE_FILE})  # defined by Geant4 during find_package
include_directories($ENV{COAST_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

# (4) Find relevant files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# (5) Define executable and link its dependencies (GEANT4 and COAST)
add_executable(Carpet2 Carpet2.cc ${sources} ${headers})
target_link_libraries(Carpet2 ${Geant4_LIBRARIES})

target_link_libraries(
  Carpet2
  $ENV{COAST_DIR}/lib/libCorsikaFileIO.so
  $ENV{COAST_DIR}/lib/libCorsikaIntern.so
)
