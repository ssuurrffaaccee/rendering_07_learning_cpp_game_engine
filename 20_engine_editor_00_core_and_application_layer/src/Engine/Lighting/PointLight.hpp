#include <rttr/registration>
#include "Engine/Lighting/Light.hpp"

using namespace rttr;

class PointLight : public Light {
public:
    PointLight();
    ~PointLight();

    virtual void set_color(glm::vec3 color) override;

    virtual void set_intensity(float intensity) override;

    float attenuation_constant() const{return attenuation_constant_;}
    void set_attenuation_constant(float attenuation_constant);

    float attenuation_linear() const{return attenuation_linear_;}
    void set_attenuation_linear(float attenuation_linear);

    float attenuation_quadratic() const{return attenuation_quadratic_;}
    void set_attenuation_quadratic(float attenuation_quadratic);

public:
    void Update() override;

private:
    float attenuation_constant_;//点光衰减常数项
    float attenuation_linear_;//点光衰减一次项
    float attenuation_quadratic_;//点光衰减二次项

    static unsigned int light_count_;//灯光数量

RTTR_ENABLE(Light);
};