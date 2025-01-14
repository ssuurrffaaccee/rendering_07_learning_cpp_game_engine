#pragma once
#include <map>
#include <string>
#include <vector>

class Shader;
class Texture2D;
class Material {
 public:
  Material();
  ~Material();

  void Parse(std::string material_path);  // 加载Material文件并解析

  void SetUniformMatrix4fv(std::string shader_property_name, float* pointer);
  void SetUniform1i(std::string shader_property_name, int value);
  /// 设置纹理
  /// \param property
  /// \param texture2D
  void SetTexture(const std::string& property, Texture2D* texture2D) ;
  Shader* shader() { return shader_; }

  std::vector<std::pair<std::string, Texture2D*>>& textures() {
    return textures_;
  }

 private:
  Shader* shader_;
  std::vector<std::pair<std::string, Texture2D*>> textures_;

  std::vector<std::pair<std::string, float*>> uniform_matrix4fv_vec;
  std::vector<std::pair<std::string, int>> uniform_1i_vec;
};