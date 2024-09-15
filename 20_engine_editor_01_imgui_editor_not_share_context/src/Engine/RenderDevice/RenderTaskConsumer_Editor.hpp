#pragma once
#include <thread>
#include "Engine/RenderDevice/RenderTaskConsumerBase.hpp"
struct GLFWwindow;
class RenderTaskBase;

/// 渲染任务消费端(编辑器)
class RenderTaskConsumerEditor : public RenderTaskConsumerBase{
public:
    RenderTaskConsumerEditor(GLFWwindow* window);
    ~RenderTaskConsumerEditor();

    virtual void InitGraphicsLibraryFramework() override;

    virtual void GetFramebufferSize(int& width,int& height) override;

    virtual void SwapBuffer() override;

private:
    GLFWwindow* window_=nullptr;
};