#include "Engine/Lighting/PointLight.hpp"
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
    registration::class_<PointLight>("PointLight")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

PointLight::PointLight():Light(),attenuation_constant_(0),attenuation_linear_(0),attenuation_quadratic_(0)
{

}

PointLight::~PointLight() {

}


void PointLight::set_color(glm::vec3 color) {
    Light::set_color(color);
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_point_light","data.color",color_);
};

void PointLight::set_intensity(float intensity) {
    Light::set_intensity(intensity);
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light","data.intensity",intensity_);
};

void PointLight::set_attenuation_constant(float attenuation_constant){
    attenuation_constant_ = attenuation_constant;
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light","data.constant",attenuation_constant_);
}

void PointLight::set_attenuation_linear(float attenuation_linear){
    attenuation_linear_ = attenuation_linear;
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light","data.linear",attenuation_linear_);
}

void PointLight::set_attenuation_quadratic(float attenuation_quadratic){
    attenuation_quadratic_ = attenuation_quadratic;
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light","data.quadratic",attenuation_quadratic_);
}

void PointLight::Update(){
    glm::vec3 light_position=game_object()->GetComponent<Transform>()->position();
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_point_light","data.pos",light_position);
}