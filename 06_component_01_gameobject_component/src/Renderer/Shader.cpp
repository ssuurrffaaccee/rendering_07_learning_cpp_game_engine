#include "Shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <iostream>

#include "Utils/Application.hpp"

std::unordered_map<std::string, Shader*> Shader::kShaderMap;

Shader::Shader() {}

Shader::~Shader() {}

Shader* Shader::Find(const std::string& shader_name) {
  std::unordered_map<std::string, Shader*>::iterator iter =
      kShaderMap.find(shader_name);
  if (iter != kShaderMap.end()) {
    return iter->second;
  }

  Shader* shader = new Shader();
  shader->Parse(shader_name);

  kShaderMap.insert(std::pair<std::string, Shader*>(shader_name, shader));

  return shader;
}

void Shader::Parse(const std::string& shader_name) {
  shader_name_ = shader_name;

  // 组装完整文件路径
  std::string vertex_shader_file_path =
      Application::data_path() + shader_name + ".vs";
  std::string fragment_shader_file_path =
      Application::data_path() + shader_name + ".fs";
  // 读取顶点Shader代码
  std::ifstream vertex_shader_input_file_stream(vertex_shader_file_path);
  std::string vertex_shader_source(
      (std::istreambuf_iterator<char>(vertex_shader_input_file_stream)),
      std::istreambuf_iterator<char>());
  // 读取片段Shader代码
  std::ifstream fragment_shader_input_file_stream(fragment_shader_file_path);
  std::string fragment_shader_source(
      (std::istreambuf_iterator<char>(fragment_shader_input_file_stream)),
      std::istreambuf_iterator<char>());

  CreateGPUProgram(vertex_shader_source.c_str(),
                   fragment_shader_source.c_str());
}

void Shader::CreateGPUProgram(const char* vertex_shader_text,
                              const char* fragment_shader_text) {
  // 创建顶点Shader
  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  // 指定Shader源码
  glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
  // 编译Shader
  glCompileShader(vertex_shader);
  // 获取编译结果
  GLint compile_status = GL_FALSE;
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_FALSE) {
    GLchar message[256];
    glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
    std::cout << "compile vs error:" << message << std::endl;
  }

  // 创建片段Shader
  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  // 指定Shader源码
  glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
  // 编译Shader
  glCompileShader(fragment_shader);
  //
  compile_status = GL_FALSE;
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_FALSE) {
    GLchar message[256];
    glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
    std::cout << "compile fs error:" << message << std::endl;
  }

  // 创建GPU程序
  gl_program_id_ = glCreateProgram();
  // 附加Shader
  glAttachShader(gl_program_id_, vertex_shader);
  glAttachShader(gl_program_id_, fragment_shader);
  // Link
  glLinkProgram(gl_program_id_);
  // 获取编译结果
  GLint link_status = GL_FALSE;
  glGetProgramiv(gl_program_id_, GL_LINK_STATUS, &link_status);
  if (link_status == GL_FALSE) {
    GLchar message[256];
    glGetProgramInfoLog(gl_program_id_, sizeof(message), 0, message);
    std::cout << "link error:" << message << std::endl;
  }
}

void Shader::Active() { glUseProgram(gl_program_id_); }

void Shader::InActive() {}