cmake_minimum_required(VERSION 3.26)
project(
  learning_cpp_game_engine
  VERSION 1.0.0
  LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(sol2)
find_package(glm)
find_package(rttr)
find_package(spdlog)


set(LINK_TARGET glm::glm RTTR::Core sol2::sol2 spdlog::spdlog)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
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


learn_step(l_lua_integrate_01_lua_call_cpp_sol2_component)
