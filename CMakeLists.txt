cmake_minimum_required(VERSION 3.22)

project (occt)
include(FetchContent)
set(node_server "https://nodejs.org/dist/v16.17.1")

set(inc_url ${node_server}/node-v16.17.1-headers.tar.xz)
set(inc_hash 554c8d1b4b16e0f4c073b9df7c49c893716a3a533f25ac646f23619f5ccee7df)

if(WIN32)
  set(lib_url ${node_server}/win-x64/node.lib)
  set(lib_hash 2f459a64647db493da63c790ce368ad54f59f086d9f22f59c5018680420197b3)
  set(pdb_url ${node_server}/win-x64/node_pdb.7z)
  set(pdb_hash 23215ce7d1e9de9777c3407239e7cf18d29d60f757b772219421ab361ac67c74)


  FetchContent_Declare(node_pdb
  URL ${pdb_url}
  URL_HASH   SHA256=${pdb_hash}
  SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodepdb)

  set(nodelib_path ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib/node.lib)
  file(DOWNLOAD ${lib_url} ${nodelib_path})

  #set(win_delay_load_hook_cc ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/src/win_delay_load_hook.cc)
  #file(DOWNLOAD https://raw.githubusercontent.com/nodejs/node-gyp/main/src/win_delay_load_hook.cc ${win_delay_load_hook_cc})
  
  FetchContent_MakeAvailable(node_pdb)
elseif(UNIX)

else()
  message(FATAL_ERROR "Unsupported platform")
endif()

FetchContent_Declare(node_include
URL ${inc_url}
URL_HASH   SHA256=${inc_hash}
SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodeinclude) 

FetchContent_Declare(node_src
URL ${node_server}/node-v16.17.1.tar.xz
URL_HASH   SHA256=6721feb4152d56d2c6b358ce397abd5a7f1daf09ee2e25c5021b9b4d3f86a330
SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodesrc) 

FetchContent_MakeAvailable(node_include node_src)

include(GNUInstallDirs)
set(CMAKE_INSTALL_RPATH $ORIGIN)

find_package(OpenCASCADE CONFIG REQUIRED COMPONENTS FoundationClasses)
message("OpenCASCADE_FOUND " ${OpenCASCADE_FOUND} ${OpenCASCADE_CONFIG})



add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE occt.cc)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})
if(WIN32)
  target_sources(${PROJECT_NAME} PRIVATE win_delay_load_hook.cc)
endif()

set(NODE_INC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/nodeinclude/include/node)

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_INC})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/node_modules/node-addon-api/")

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_link_libraries(${PROJECT_NAME} PRIVATE ${nodelib_path} TKernel TKMath)


install(TARGETS ${PROJECT_NAME})
install(IMPORTED_RUNTIME_ARTIFACTS TKernel TKMath)

