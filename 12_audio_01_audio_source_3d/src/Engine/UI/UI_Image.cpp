#include "Engine/UI/UI_Image.hpp"

#include <rttr/registration>
#include <vector>

#include "Engine/Component/GameObject.hpp"
#include "Engine/RenderDevice/RenderDevice.hpp"
#include "Engine/Renderer/Material.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Texture2D.hpp"
#include "Engine/Utils/Debug.hpp"

using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<UIImage>("UIImage").constructor<>()(
      rttr::policy::ctor::as_raw_ptr);
}

UIImage::UIImage() : Component(), texture2D_(nullptr), width_(0), height_(0) {}

UIImage::~UIImage() {}

void UIImage::Update() {
  Component::Update();
  if (texture2D_ == nullptr) {
    return;
  }
  MeshFilter* mesh_filter =
      dynamic_cast<MeshFilter*>(game_object()->GetComponent("MeshFilter"));
  if (mesh_filter == nullptr) {
    // 创建 MeshFilter
    std::vector<MeshFilter::Vertex> vertex_vector = {
        {{0.f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.f, 0.f}},
        {{texture2D_->width(), 0.0f, 0.0f},
         {1.0f, 1.0f, 1.0f, 1.0f},
         {1.f, 0.f}},
        {{texture2D_->width(), texture2D_->height(), 0.0f},
         {1.0f, 1.0f, 1.0f, 1.0f},
         {1.f, 1.f}},
        {{0.f, texture2D_->height(), 0.0f},
         {1.0f, 1.0f, 1.0f, 1.0f},
         {0.f, 1.f}}};
    std::vector<unsigned short> index_vector = {0, 1, 2, 0, 2, 3};
    mesh_filter =
        dynamic_cast<MeshFilter*>(game_object()->AddComponent("MeshFilter"));
    mesh_filter->CreateMesh(vertex_vector, index_vector);

    // 创建 Material
    auto material = new Material();  // 设置材质
    material->Parse("material/ui_image.mat");
    material->SetTexture("u_diffuse_texture", texture2D_);

    // 挂上 MeshRenderer 组件
    auto mesh_renderer = dynamic_cast<MeshRenderer*>(
        game_object()->AddComponent("MeshRenderer"));
    mesh_renderer->SetMaterial(material);
  }
}

void UIImage::OnPreRender() {
  Component::OnPreRender();
  glStencilFunc(GL_EQUAL, 0x1,
                0xFF);  // 等于1 通过测试 ,就是上次绘制的图 的范围 才通过测试。
  glStencilOp(GL_KEEP, GL_KEEP,
              GL_KEEP);  // 没有通过测试的，保留原来的，也就是保留上一次的值。
}

void UIImage::OnPostRender() {
  Component::OnPostRender();
  RenderDevice::instance()->Disable(RenderDevice::RenderState::STENCIL_TEST);
}
