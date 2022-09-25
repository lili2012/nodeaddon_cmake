cmake_minimum_required(VERSION 3.22)

project (occt)
# get CMAKE_JS variables
include(GNUInstallDirs)
message(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_FULL__BINDIR})
set(CMAKE_INSTALL_RPATH $ORIGIN)
#set(OpenCASCADE_ROOT "/home/shulian/Desktop/OCCT/lib/cmake/opencascade/")
find_package(OpenCASCADE CONFIG REQUIRED COMPONENTS FoundationClasses)

#include_directories(${OpenCASCADE_INCLUDE_DIR})

set(SOURCE_FILES occt.cc)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/node_modules/node-addon-api/")

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_JS_LIB} TKernel TKMath)


install(TARGETS ${PROJECT_NAME})
install(IMPORTED_RUNTIME_ARTIFACTS TKernel TKMath)