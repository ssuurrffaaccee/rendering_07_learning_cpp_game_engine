#include "Renderer/Camera.hpp"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <rttr/registration>

#include "Component/GameObject.hpp"
#include "Component/Transform.hpp"

using namespace rttr;
RTTR_REGISTRATION  // 注册反射
{
  registration::class_<Camera>("Camera").constructor<>()(
      rttr::policy::ctor::as_raw_ptr);
}

Camera::Camera()
    : clear_color_(49.f / 255, 77.f / 255, 121.f / 255, 1.f),
      clear_flag_(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {}

Camera::~Camera() {}

void Camera::SetView(const glm::vec3 &cameraForward,
                     const glm::vec3 &cameraUp) {
  auto transform =
      dynamic_cast<Transform *>(game_object()->GetComponent("Transform"));
  view_mat4_ = glm::lookAt(transform->position(), cameraForward, cameraUp);
}

void Camera::SetProjection(float fovDegrees, float aspectRatio, float nearClip,
                           float farClip) {
  projection_mat4_ = glm::perspective(glm::radians(fovDegrees), aspectRatio,
                                      nearClip, farClip);
}

void Camera::Clear() {
  glClear(clear_flag_);
  glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
}