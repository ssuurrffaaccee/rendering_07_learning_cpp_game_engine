#pragma once
#include "Engine/Renderer/Camera.hpp"

class UICamera : public Camera {
 public:
  UICamera();
  RTTR_ENABLE(Camera);
};