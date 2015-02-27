cmake_minimum_required (VERSION 2.8.0)
project(MNI)

set(WORKSPACE_DIR ..)

add_subdirectory (src)

add_executable(MNI ${SRC_LIST})

message(${CMAKE_BINARY_DIR}/llvm/Debug/lib/)

if(WIN32)
target_link_libraries(MNI ${CMAKE_BINARY_DIR}/llvm/Debug/lib/clang-model-generator.imp)
else(WIN32)
#target_link_libraries(MNI ${CMAKE_BINARY_DIR}/llvm/lib/libclang-model-generator.so)
target_link_libraries(MNI clang-model-generator)
target_link_libraries(MNI boost_filesystem boost_system)
endif(WIN32)
include_directories(${WORKSPACE_DIR}/llvm/tools/clang/tools/clang-model-generator/src)

set_property(TARGET MNI PROPERTY CXX_STANDARD 14)


if(WIN32)
add_custom_command(TARGET MNI PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/Debug/clang-model-generator.dll"	# in-file
        ${CMAKE_BINARY_DIR}/mni/Debug)								# out-file path
endif(WIN32)



##############
# ChaiScript #
##############
# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)
ExternalProject_Add(
    ChaiScript
	SVN_REPOSITORY https://github.com/ChaiScript/ChaiScript/tags/v5.6.0
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=Debug
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=Release
    # Disable install step
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    # Wrap configure and build steps in a script to log output
    LOG_CONFIGURE ON
    LOG_BUILD ON
)
ExternalProject_Get_Property(ChaiScript SOURCE_DIR)
include_directories(${SOURCE_DIR}/include)
add_dependencies(MNI ChaiScript)