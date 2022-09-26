cmake_minimum_required(VERSION 3.22)

project (occt)
include(FetchContent)
include(GNUInstallDirs)


set(CMAKE_INSTALL_RPATH $ORIGIN)
find_package(OpenCASCADE CONFIG REQUIRED COMPONENTS FoundationClasses)
set(node_server "https://nodejs.org/dist/v16.17.1")
FetchContent_Declare(node_include
URL ${node_server}/node-v16.17.1-headers.tar.xz
URL_HASH   SHA256=554c8d1b4b16e0f4c073b9df7c49c893716a3a533f25ac646f23619f5ccee7df
SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodeinclude) 

FetchContent_Declare(node_src
URL ${node_server}/node-v16.17.1.tar.xz
URL_HASH   SHA256=6721feb4152d56d2c6b358ce397abd5a7f1daf09ee2e25c5021b9b4d3f86a330
SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodesrc) 

FetchContent_MakeAvailable(node_include node_src)

set(SOURCE_FILES occt.cc)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})


set(NODE_INC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodeinclude/include/node)

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_INC})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/node_modules/node-addon-api/")

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB} TKernel TKMath)


install(TARGETS ${PROJECT_NAME})
install(IMPORTED_RUNTIME_ARTIFACTS TKernel TKMath)

