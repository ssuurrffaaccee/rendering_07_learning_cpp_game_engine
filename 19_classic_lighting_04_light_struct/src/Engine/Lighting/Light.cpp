#include "Engine/Lighting/Light.hpp"
#include <rttr/registration>
#include "Engine/Component/GameObject.hpp"
#include "Engine/Component/Transform.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Material.hpp"
using namespace rttr;
RTTR_REGISTRATION//注册反射
{
    registration::class_<Light>("Light")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

Light::Light():Component() {}

Light::~Light() {}

void Light::Update() {
    GameObject::Foreach([this](GameObject* iterate_game_object){
        if(iterate_game_object->active() == false){
            return;
        }
        MeshRenderer* mesh_renderer=iterate_game_object->GetComponent<MeshRenderer>();
        if(mesh_renderer== nullptr){
            return;
        }
        Material* material = mesh_renderer->material();
        //设置灯光位置、颜色、强度
        glm::vec3 light_position=game_object()->GetComponent<Transform>()->position();
        material->SetUniform3f("u_light.pos",light_position);
        material->SetUniform3f("u_light.color",color_);
        material->SetUniform1f("u_light.intensity",intensity_);
    });
}