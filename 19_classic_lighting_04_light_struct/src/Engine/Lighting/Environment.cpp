#include "Engine/Lighting/Environment.hpp"
#include "Engine/Component/GameObject.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Material.hpp"

Environment::Environment():
    ambient_color_(glm::vec3(1.0f, 1.0f, 1.0f)),ambient_color_intensity_(1.0f) {
}

void Environment::Update() {
    GameObject::Foreach([this](GameObject* game_object){
        if(game_object->active()==false){
            return;
        }
        MeshRenderer* mesh_renderer=game_object->GetComponent<MeshRenderer>();
        if(mesh_renderer== nullptr){
            return;
        }
        Material* material = mesh_renderer->material();
        material->SetUniform3f("u_ambient.light_color",ambient_color_);
        material->SetUniform1f("u_ambient.light_intensity",ambient_color_intensity_);
    });
}