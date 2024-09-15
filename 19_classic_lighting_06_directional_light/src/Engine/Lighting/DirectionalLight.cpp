#include "Engine/Lighting/DirectionalLight.hpp"
#include <rttr/registration>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Engine/Component/GameObject.hpp"
#include "Engine/Component/Transform.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Material.hpp"
#include "Engine/RenderDevice/UniformBufferObjectManager.hpp"

using namespace rttr;
RTTR_REGISTRATION//注册反射
{
    registration::class_<DirectionalLight>("DirectionalLight")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

DirectionalLight::DirectionalLight():Light() {
}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::set_color(glm::vec3 color) {
    Light::set_color(color);
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_directional_light","data.color",color_);
};

void DirectionalLight::set_intensity(float intensity) {
    Light::set_intensity(intensity);
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_directional_light","data.intensity",intensity_);
};

void DirectionalLight::Update() {
    glm::vec3 rotation=game_object()->GetComponent<Transform>()->rotation();
    glm::mat4 eulerAngleYXZ = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));
    glm::vec3 light_rotation=glm::vec3(eulerAngleYXZ * glm::vec4(0,0,-1,0));//Transform旋转 * 默认朝向
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_directional_light","data.dir",light_rotation);
}