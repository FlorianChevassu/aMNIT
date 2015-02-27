cmake_minimum_required(VERSION 2.8)

set(SRC_LIST ${SRC_LIST}
${CMAKE_CURRENT_SOURCE_DIR}/ClangASTConsumer.h;
${CMAKE_CURRENT_SOURCE_DIR}/ClangASTVisitor.h;
${CMAKE_CURRENT_SOURCE_DIR}/ClangASTVisitor.cpp;
${CMAKE_CURRENT_SOURCE_DIR}/ClangFrontendAction.h;
${CMAKE_CURRENT_SOURCE_DIR}/ClangFrontendActionFactory.h;
${CMAKE_CURRENT_SOURCE_DIR}/ClangUtils.h;
${CMAKE_CURRENT_SOURCE_DIR}/CommandLineArgumentsAdjuster.h;
${CMAKE_CURRENT_SOURCE_DIR}/CommandLineArgumentsAdjuster.cpp;
#${CMAKE_CURRENT_SOURCE_DIR}/Frontend.h;
#${CMAKE_CURRENT_SOURCE_DIR}/Frontend.cpp;
PARENT_SCOPE)
