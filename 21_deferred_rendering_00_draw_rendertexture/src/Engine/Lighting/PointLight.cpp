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

unsigned int PointLight::light_count_=0;

PointLight::PointLight():Light(),attenuation_constant_(0),attenuation_linear_(0),attenuation_quadratic_(0)
{
    light_id_=light_count_;
    light_count_++;
    UniformBufferObjectManager::UpdateUniformBlockSubData1i("u_point_light_array","actually_used_count",light_count_);
}

PointLight::~PointLight() {

}


void PointLight::set_color(glm::vec3 color){
    Light::set_color(color);
    std::string uniform_block_member_name=fmt::format("data[{}].color",light_id_);
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_point_light_array",uniform_block_member_name,color_);
};

void PointLight::set_intensity(float intensity){
    Light::set_intensity(intensity);
    std::string uniform_block_member_name=fmt::format("data[{}].intensity",light_id_);
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light_array",uniform_block_member_name,intensity_);
};

void PointLight::set_attenuation_constant(float attenuation_constant){
    attenuation_constant_ = attenuation_constant;
    std::string uniform_block_member_name=fmt::format("data[{}].constant",light_id_);
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light_array",uniform_block_member_name,attenuation_constant_);
}

void PointLight::set_attenuation_linear(float attenuation_linear){
    attenuation_linear_ = attenuation_linear;
    std::string uniform_block_member_name=fmt::format("data[{}].linear",light_id_);
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light_array",uniform_block_member_name,attenuation_linear_);
}

void PointLight::set_attenuation_quadratic(float attenuation_quadratic){
    attenuation_quadratic_ = attenuation_quadratic;
    std::string uniform_block_member_name=fmt::format("data[{}].quadratic",light_id_);
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_point_light_array",uniform_block_member_name,attenuation_quadratic_);
}

void PointLight::Update(){
    glm::vec3 light_position=game_object()->GetComponent<Transform>()->position();
    std::string uniform_block_member_name=fmt::format("data[{}].pos",light_id_);
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_point_light_array",uniform_block_member_name,light_position);
}