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


set(LINK_TARGET glm::glm glfw stb::stb glad::glad)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif()

set(STEP_NAME 02_texture_00_load_image)
set(SRC_FILES main.cpp Texture2D.cpp)
add_executable(${STEP_NAME} ${SRC_FILES})
target_link_libraries(${STEP_NAME} ${LINK_TARGET})
install(TARGETS ${STEP_NAME} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin/)


