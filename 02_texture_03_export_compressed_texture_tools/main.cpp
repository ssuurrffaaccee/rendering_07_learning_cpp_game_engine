#include <glad/glad.h>

#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "Texture2D.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow *window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location, u_diffuse_texture_location,
    a_uv_location;
Texture2D *texture2d = nullptr;

// 初始化OpenGL
void init_opengl() {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  // gladLoadGL(glfwGetProcAddress);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(1);
}
void InitSpdLog() {
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[image_compress] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "logs/image_compress.txt", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sink_list = {file_sink, console_sink};

    // you can even set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>(
        "image_compress", spdlog::sinks_init_list({console_sink, file_sink})));
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
  }
}

int main(int argc, char **argv) {
  InitSpdLog();

  init_opengl();

  for (int i = 1; i < argc; ++i) {
    // 从GPU中，将显存中保存的压缩好的纹理数据，下载到内存，并保存到硬盘。
    std::string src_image_file_path(argv[i]);
    spdlog::info("src_image_file_path:{}", src_image_file_path);
    std::string cpt_file_path = src_image_file_path;
    auto last_index_of_point = cpt_file_path.find_last_of('.');
    cpt_file_path.replace(last_index_of_point,
                          cpt_file_path.size() - last_index_of_point, ".cpt");
    Texture2D::CompressImageFile(src_image_file_path, cpt_file_path);
  }

  spdlog::info("finish");
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}