#include "Engine/Lighting/Environment.hpp"
#include "Engine/Component/GameObject.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Material.hpp"
#include "Engine/RenderDevice/GPUResourceMapper.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"
#include "Engine/RenderDevice/UniformBufferObjectManager.hpp"
Environment::Environment():
    ambient_color_(glm::vec3(1.0f, 1.0f, 1.0f)),ambient_color_intensity_(1.0f) {
}

/// 设置环境颜色
void Environment::set_ambient_color(const glm::vec3 &ambient_color) {
    ambient_color_ = ambient_color;
    UniformBufferObjectManager::UpdateUniformBlockSubData3f("u_ambient","data.color",ambient_color_);
}


/// 设置环境强度
void Environment::set_ambient_color_intensity(float ambient_color_intensity){
    ambient_color_intensity_ = ambient_color_intensity;
    UniformBufferObjectManager::UpdateUniformBlockSubData1f("u_ambient","data.intensity",ambient_color_intensity_);
}