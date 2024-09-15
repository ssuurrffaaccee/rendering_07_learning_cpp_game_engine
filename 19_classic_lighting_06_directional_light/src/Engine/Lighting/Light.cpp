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


Light::Light():Component() {

}

Light::~Light() {}