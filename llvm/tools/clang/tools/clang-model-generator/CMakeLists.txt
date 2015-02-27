add_definitions(-DCLANG_MODEL_GENERATOR_COMPILE)


###########################
#   adding the sources    #
###########################
add_subdirectory(src)
include_directories(src INCLUDE_LIST)

###############################
#   organizing the sources    #
###############################

SOURCE_GROUP(src FILES ${MAIN_SRC_LIST})
SOURCE_GROUP(src\\CMG\\frontend FILES ${FRONTEND_SRC_LIST})
SOURCE_GROUP(src\\CMG\\model FILES ${MODEL_SRC_LIST})

set(LLVM_LINK_COMPONENTS
  support
  )

add_clang_library(clang-model-generator SHARED ${MAIN_SRC_LIST} ${FRONTEND_SRC_LIST} ${MODEL_SRC_LIST})

##############################
#   set standard to C++14    #
##############################
set_property(TARGET clang-model-generator PROPERTY CXX_STANDARD 14)

target_link_libraries(clang-model-generator PUBLIC
clangFrontend
clangSerialization
clangDriver
clangTooling
clangParse
clangSema
clangStaticAnalyzerFrontend
clangStaticAnalyzerCheckers
clangStaticAnalyzerCore
clangAnalysis
clangRewriteFrontend
clangRewrite
clangEdit
clangAST
clangLex
clangBasic
clangIndex)

if(WIN32)
    add_custom_command(TARGET clang-model-generator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/llvm/Debug/bin/clang-model-generator.dll"	# in-file
            ${CMAKE_BINARY_DIR}/Debug)										# out-file path
    #add_custom_command(TARGET clang-model-generator POST_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #        "${CMAKE_BINARY_DIR}/llvm/Release/bin/clang-model-generator.dll"	# in-file
    #        ${CMAKE_BINARY_DIR}/Release)										# out-file path
endif(WIN32)