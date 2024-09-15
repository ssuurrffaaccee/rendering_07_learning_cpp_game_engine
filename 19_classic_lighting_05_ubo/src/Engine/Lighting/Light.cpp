#include "Engine/Lighting/Light.hpp"
#include <rttr/registration>
#include "Engine/Component/GameObject.hpp"
#include "Engine/Component/Transform.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Material.hpp"
#include "Engine/RenderDevice/UniformBufferObjectManager.hpp"
using namespace rttr;
RTTR_REGISTRATION//注册反射
{
    registration::class_<Light>("Light")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

Light::Light():Component() {}

Light::~Light() {}

void Light::Update(){
    glm::vec3 light_position=game_object()->GetComponent<Transform>()->position();
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_light","data.pos",light_position);
}

void Light::set_color(glm::vec3 color){
    color_ = color;
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_light","data.color",color_);
};

void Light::set_intensity(float intensity){
    intensity_ = intensity;
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_light","data.intensity",intensity_);
};