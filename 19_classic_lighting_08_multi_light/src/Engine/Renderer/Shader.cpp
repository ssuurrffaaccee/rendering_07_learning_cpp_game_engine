#include "Shader.hpp"

#include <glad/glad.h>

#include <fstream>
#include <iostream>

#include "Engine/Utils/Application.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"
#include "Engine/RenderDevice/GPUResourceMapper.hpp"

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
  CreateShaderProgram(vertex_shader_source.c_str(),
                   fragment_shader_source.c_str());
  ConnectUniformBlockAndBindingPoint();
}

void Shader::CreateShaderProgram(const char* vertex_shader_text,
                              const char* fragment_shader_text) {
  //编译Shader任务
  shader_program_handle_=GPUResourceMapper::GenerateShaderProgramHandle();
  RenderTaskProducer::ProduceRenderTaskCompileShader(vertex_shader_text, fragment_shader_text, shader_program_handle_);
}
void Shader::ConnectUniformBlockAndBindingPoint() {
    RenderTaskProducer::ProduceRenderTaskConnectUniformBlockAndBindingPoint(shader_program_handle_);
}
void Shader::Active() {     
  //使用Shader程序任务
  RenderTaskProducer::ProduceRenderTaskUseShaderProgram(shader_program_handle_);
}

void Shader::InActive() {}