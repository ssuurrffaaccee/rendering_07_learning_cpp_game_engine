cmake_minimum_required(VERSION 3.26)
project(
  learning_cpp_game_engine
  VERSION 1.0.0
  LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(glm)
find_package(spdlog)

set(LINK_TARGET glm::glm spdlog::spdlog)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
   include_directories("${PROJECT_SOURCE_DIR}/../resources/non_open_src_depends/fbx_sdk_2020.2.1/include")
   link_directories("${PROJECT_SOURCE_DIR}/../resources/non_open_src_depends/fbx_sdk_2020.2.1/win/lib/vs2019/x64/release")
   link_libraries(libfbxsdk-md libxml2-md zlib-md)
   file(COPY "${PROJECT_SOURCE_DIR}/../resources/non_open_src_depends/fbx_sdk_2020.2.1/win/lib/vs2019/x64/release/libfbxsdk.dll" DESTINATION "${PROJECT_SOURCE_DIR}/bin")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
   include_directories("${PROJECT_SOURCE_DIR}/../resources/non_open_src_depends/fbx_sdk_2020.2.1/include")
   link_directories("${PROJECT_SOURCE_DIR}/../resources/non_open_src_depends/fbx_sdk_2020.2.1/mac/lib/clang/release")
   link_libraries(fbxsdk)
   file(COPY "${PROJECT_SOURCE_DIR}/../resources/non_open_src_depends/fbx_sdk_2020.2.1/mac/lib/clang/release/libfbxsdk.dylib" DESTINATION "${PROJECT_SOURCE_DIR}/bin")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif()

function(learn_step step_name)  
    file(GLOB_RECURSE SRC_FILES_CPP CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.cxx")
    set(SRC_FILES ${SRC_FILES_CPP})
    add_executable(${step_name} ${SRC_FILES})
    target_link_libraries(${step_name} ${LINK_TARGET})
    target_include_directories(${step_name} PRIVATE "${PROJECT_SOURCE_DIR}/src")
    install(TARGETS ${step_name} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
endfunction()

learn_step(17_load_fbx_01_extra_mesh_with_normal)
