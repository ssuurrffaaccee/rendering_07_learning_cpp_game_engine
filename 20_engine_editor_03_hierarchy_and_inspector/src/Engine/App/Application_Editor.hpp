#pragma once
#include <string>
#include "Engine/App/ApplicationBase.hpp"
#include "Engine/DataStructure/Tree.hpp"

struct GLFWwindow;
class ApplicationEditor : public ApplicationBase{
public:
    ApplicationEditor():ApplicationBase(){}
    ~ApplicationEditor(){}

    void Run() override;
    /// 绘制节点结构
    /// \param node
    /// \param label
    /// \param base_flags
    void DrawHierarchy(Tree::Node* node,const char* label,int base_flags);
public:
    /// 初始化图形库，例如glfw
    virtual void InitGraphicsLibraryFramework() override;

    virtual void Exit() override;
private:
    GLFWwindow* editor_glfw_window_;//编辑器窗口
    GLFWwindow* game_glfw_window_;//游戏窗口
    Tree::Node* selected_node_=nullptr;//记录Hierarchy当前选中的Node
};
