#pragma once
#include <glm/glm.hpp>

#include "Engine/Component/Component.hpp"
#include "Engine/Component/GameObject.hpp"
class Material;
class MeshFilter;
class Texture2D;
class MeshRenderer : public Component {
 public:
  MeshRenderer();
  ~MeshRenderer();
  void SetMaterial(Material* material);  // 设置Material
  Material* material() { return material_; }

  void Render();  // 渲染
 private:
  Material* material_;

  unsigned int vertex_buffer_object_ = 0;   // 顶点缓冲区对象
  unsigned int element_buffer_object_ = 0;  // 索引缓冲区对象
  unsigned int vertex_array_object_ = 0;    // 顶点数组对象
  RTTR_ENABLE(Component);
};