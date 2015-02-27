cmake_minimum_required(VERSION 2.8.0)
project(MNI)

set(MNI_BINARY_DIR ${CMAKE_BINARY_DIR})
############################################
#   enable exceptions and RTTI for LLVM    #
############################################
set(LLVM_ENABLE_EH ON)
set(LLVM_ENABLE_RTTI ON)

# Enable ExternalProject CMake module
include(ExternalProject)

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(llvm)
add_subdirectory(mni)
