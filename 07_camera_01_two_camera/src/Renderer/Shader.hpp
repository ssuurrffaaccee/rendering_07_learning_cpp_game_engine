#pragma once
#include <string>
#include <unordered_map>

class Shader {
 public:
  Shader();
  ~Shader();

 public:
  void Parse(const std::string& shader_name);  // 加载Shader文件并解析
  void CreateGPUProgram(
      const char* vertex_shader_text,
      const char* fragment_shader_text);  // 编译Shader,创建GPU程序;

  void Active();    // 激活
  void InActive();  // 禁用

  unsigned int gl_program_id() {
    return gl_program_id_;
  }  // glCreateProgram()返回的GPU程序句柄;

 private:
  std::string shader_name_;     // shader名
  unsigned int gl_program_id_;  // glCreateProgram()返回的GPU程序句柄;

 public:
  static Shader* Find(const std::string& shader_name);  // 查找或创建Shader
 private:
  static std::unordered_map<std::string, Shader*>
      kShaderMap;  // 已经创建的Shader
};