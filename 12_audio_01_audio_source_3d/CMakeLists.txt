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

set(LINK_TARGET glm::glm glfw stb::stb glad::glad spdlog::spdlog Freetype::Freetype rapidxml::rapidxml RTTR::Core)

include_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/")
link_directories("${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/core/lib/x64")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    link_libraries(fmod_vc)
    file(COPY "${CMAKE_SOURCE_DIR}/../resources/non_open_src_depends/fmod/api/core/lib/x64/fmod.dll" DESTINATION "${CMAKE_SOURCE_DIR}/bin/")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    link_libraries(fmod)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif()

function(learn_step step_name)  
    file(GLOB_RECURSE SRC_FILES_CPP CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
    set(SRC_FILES ${SRC_FILES_CPP})
    add_executable(${step_name} ${SRC_FILES})
    target_link_libraries(${step_name} ${LINK_TARGET})
    target_include_directories(${step_name} PRIVATE "${PROJECT_SOURCE_DIR}/src")
    install(TARGETS ${step_name} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
endfunction()


learn_step(12_audio_01_audio_source_3d)
