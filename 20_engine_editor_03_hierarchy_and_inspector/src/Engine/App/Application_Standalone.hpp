#pragma once
#include <string>
#include "Engine/App/ApplicationBase.hpp"

class GLFWwindow;
class ApplicationStandalone : public ApplicationBase{
public:
    ApplicationStandalone():ApplicationBase(){}
    ~ApplicationStandalone(){}

    void Run() override;

public:
    /// 初始化图形库，例如glfw
    virtual void InitGraphicsLibraryFramework() override;

    virtual void Exit() override;
private:
    GLFWwindow* glfw_window_;
};
