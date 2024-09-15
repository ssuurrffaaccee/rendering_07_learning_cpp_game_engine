#pragma once
#include <string>
#include "Engine/App/ApplicationBase.hpp"

struct GLFWwindow;
class ApplicationEditor : public ApplicationBase{
public:
    ApplicationEditor():ApplicationBase(){}
    ~ApplicationEditor(){}

    void Run() override;

public:
    /// 初始化图形库，例如glfw
    virtual void InitGraphicsLibraryFramework() override;

    virtual void Exit() override;
private:
    GLFWwindow* editor_glfw_window_;//编辑器窗口
    GLFWwindow* game_glfw_window_;//游戏窗口
};
