#pragma once
#include <string>
#include <unordered_map>

class Shader {
 public:
  Shader();
  ~Shader();

 public:
  void Parse(const std::string& shader_name);  // 加载Shader文件并解析
  void CreateShaderProgram(const char* vertex_shader_text, const char* fragment_shader_text);//编译Shader,创建Shader程序;
  /// 串联uniform block与binding point。GL初始化时，已经串联了UBO和binding point，这样三者就联系起来了。
  /// 当前shader程序执行到需要uniform block的数据时，就以它的index，找到binding point。
  /// 而binding point与UBO是一一对应的，那么就找到UBO取数据。
  /// 如此，后续更新UBO数据，就会直接影响到Shader程序中的uniform block值。
  void ConnectUniformBlockAndBindingPoint();
  void Active();    // 激活
  void InActive();  // 禁用

  unsigned int shader_program_handle(){return shader_program_handle_;}//Shader程序句柄;
 private:
  std::string shader_name_;     // shader名
  unsigned int shader_program_handle_;//Shader程序句柄;
  std::unordered_map<std::string,unsigned int> uniform_block_binding_point_map_;//uniform black对应的binding point;
 public:
  static Shader* Find(const std::string& shader_name);  // 查找或创建Shader
 private:
  static std::unordered_map<std::string, Shader*>
      kShaderMap;  // 已经创建的Shader
};