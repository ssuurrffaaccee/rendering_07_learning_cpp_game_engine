#pragma once
#include <glm/glm.hpp>
#include "Engine/Component/Component.hpp"

//~zh 灯光
class Light: public Component {
public:
    Light();
    ~Light();

    glm::vec3 color() const{return color_;};
    void set_color(glm::vec3 color){color_ = color;};

    float intensity() const{return intensity_;};
    void set_intensity(float intensity){intensity_ = intensity;};

public:
    void Update() override;

private:
    glm::vec3 color_;//颜色
    float intensity_;//强度

RTTR_ENABLE(Component);
};
