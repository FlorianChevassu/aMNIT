cmake_minimum_required(VERSION 2.8)

add_subdirectory(frontends)
add_subdirectory(model)

set(FRONTEND_SRC_LIST ${FRONTEND_SRC_LIST} PARENT_SCOPE)
set(MODEL_SRC_LIST ${MODEL_SRC_LIST} PARENT_SCOPE)
