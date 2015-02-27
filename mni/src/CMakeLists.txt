

add_subdirectory(templateEngine)
add_subdirectory(model)

set(SRC_LIST ${SRC_LIST}
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp;
PARENT_SCOPE)
