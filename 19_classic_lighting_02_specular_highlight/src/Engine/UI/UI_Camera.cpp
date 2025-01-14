#include "Engine/UI/UI_Camera.hpp"

#include <rttr/registration>

using namespace rttr;
RTTR_REGISTRATION  // 注册反射
{
  registration::class_<UICamera>("UICamera")
      .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UICamera::UICamera() : Camera() { camera_use_for_ = CameraUseFor::UI; }
