#pragma once
#include <rttr/registration>
#include "Engine/Lighting/Light.hpp"

using namespace rttr;

class DirectionalLight : public Light {
public:
    DirectionalLight();
    ~DirectionalLight();

    virtual void set_color(glm::vec3 color) override;

    virtual void set_intensity(float intensity) override;

public:
    void Update() override;

private:
    static unsigned int light_count_;//灯光数量

RTTR_ENABLE(Light);
};
