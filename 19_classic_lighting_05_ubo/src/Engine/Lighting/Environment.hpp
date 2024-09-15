#pragma once
#include <glm/glm.hpp>


/// 环境配置
class Environment {
public:
    Environment();

    /// 设置环境颜色
    void set_ambient_color(const glm::vec3 &ambient_color);

    /// 获取环境颜色
    const glm::vec3 &ambient_color() const{return ambient_color_;}

    /// 设置环境强度
    void set_ambient_color_intensity(float ambient_color_intensity);

    /// 获取环境强度
    float ambient_color_intensity() const{return ambient_color_intensity_;}
private:
    glm::vec3 ambient_color_;// 环境颜色
    float ambient_color_intensity_;// 环境颜色强度

    unsigned int uniform_buffer_object_handle_=0;//Uniform缓冲区对象句柄
};

