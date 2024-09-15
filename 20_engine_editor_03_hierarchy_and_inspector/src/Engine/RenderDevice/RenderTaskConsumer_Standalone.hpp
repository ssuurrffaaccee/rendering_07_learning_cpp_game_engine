#pragma once
#include <thread>
#include "Engine/RenderDevice/RenderTaskConsumerBase.hpp"

class GLFWwindow;
class RenderTaskBase;

/// 渲染任务消费端(PC系统游戏程序)
class RenderTaskConsumerStandalone : public RenderTaskConsumerBase{
public:
    RenderTaskConsumerStandalone(GLFWwindow* window);
    ~RenderTaskConsumerStandalone();

    virtual void InitGraphicsLibraryFramework() override;

    virtual void GetFramebufferSize(int& width,int& height) override;

    virtual void SwapBuffer() override;

private:
    GLFWwindow* window_=nullptr;
};
