#pragma once
#include <thread>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();

private:
    /// 渲染线程主函数
    void RenderMain();
private:
    GLFWwindow* window_;//glfw创建的窗口
    std::thread render_thread_;//渲染线程
};

