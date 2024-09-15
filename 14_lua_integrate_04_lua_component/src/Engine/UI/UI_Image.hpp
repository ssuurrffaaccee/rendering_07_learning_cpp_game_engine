#pragma once
#include "Engine/Component/Component.hpp"
#include "Engine/Renderer/MeshFilter.hpp"
#include "Engine/Renderer/Texture2D.hpp"

class UIImage : public Component {
 public:
  UIImage();
  ~UIImage() override;
  Texture2D* texture2D() { return texture2D_; }
  void set_texture(Texture2D* texture2D) {
    texture2D_ = texture2D;
    width_ = texture2D->width();
    height_ = texture2D->height();
  }

  int width() { return width_; }
  int height() { return height_; }

 public:
  void Update() override;
  /// 渲染之前
  void OnPreRender() override;

  void OnPostRender() override;

 private:
  Texture2D* texture2D_;  // Texture
  int width_;
  int height_;
  RTTR_ENABLE();
};
