cmake_minimum_required(VERSION 3.26)
project(
  learning_cpp_game_engine
  VERSION 1.0.0
  LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(glfw3)
find_package(glad)
find_package(glm)
find_package(stb)
find_package(spdlog)
find_package(rapidxml)
find_package(rttr)
find_package(freetype)
find_package(easy_profiler)
find_package(sol2)

set(LINK_TARGET glm::glm glfw easy_profiler sol2::sol2 stb::stb glad::glad spdlog::spdlog Freetype::Freetype rapidxml::rapidxml RTTR::Core)

include_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/")

# begin fmod 
include_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/core/inc")
include_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/studio/inc")
link_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/core/lib/x64")
link_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/studio/lib/x64")
# end fmod

#begin fmod
include(CMakeLists.txt.luasocket)
#end fmod

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(MSVC ON)
    link_libraries(fmod_vc fmodstudio_vc)
    file(COPY "${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/core/lib/x64/fmod.dll" DESTINATION "${CMAKE_SOURCE_DIR}/bin/")
    file(COPY "${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/studio/lib/x64/fmodstudio.dll" DESTINATION "${CMAKE_SOURCE_DIR}/bin/")
    add_compile_options("/bigobj")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    link_libraries(fmod fmodstudio)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif()

function(learn_step step_name)  
    file(GLOB_RECURSE SRC_FILES_CPP CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
    set(SRC_FILES ${SRC_FILES_CPP})
    add_executable(${step_name} ${SRC_FILES} ${luasocket_c})
    target_link_libraries(${step_name} ${LINK_TARGET})
    target_include_directories(${step_name} PRIVATE "${PROJECT_SOURCE_DIR}/src")
    install(TARGETS ${step_name} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
endfunction()

add_definitions(-D USE_FMOD_STUDIO)
learn_step(16_skinned_mesh_renderer_00_simple_skinned_mesh_renderer)
