#include "Engine/App/ApplicationBase.hpp"
#include <memory>
#include <iostream>
#include "rttr/registration"
#include "easy/profiler.h"
#include "Engine/Utils/Debug.hpp"
#include "Engine/Component/GameObject.hpp"
#include "Engine/Renderer/Camera.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Shader.hpp"
#include "Engine/Control/Input.hpp"
#include "Engine/Utils/Screen.hpp"
#include "Engine/RenderDevice/RenderTaskConsumer.hpp"
#include "Engine/Audio/Audio.hpp"
#include "Engine/Utils/Time.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"
#include "Engine/LuaBinding/LuaBinding.hpp"


void ApplicationBase::Init() {
    EASY_MAIN_THREAD;
    profiler::startListen();// 启动profiler服务器，等待gui连接。

    Debug::Init();
    DEBUG_LOG_INFO("game start");

    InitLuaBinding();
    LoadConfig();

    Time::Init();

    //初始化图形库，例如glfw
    InitGraphicsLibraryFramework();

    UpdateScreenSize();

    //初始化 fmod
    Audio::Init();
}

/// 初始化图形库，例如glfw
void ApplicationBase::InitGraphicsLibraryFramework() {

}

void ApplicationBase::InitLuaBinding() {
    //设置lua搜索目录
    LuaBinding::Init(";./lua/?.lua;");
    //绑定引擎所有类到Lua
    LuaBinding::BindLua();
    //执行lua
    LuaBinding::RunLuaFile("./lua/config.lua");
}

void ApplicationBase::LoadConfig() {
    sol::state& sol_state=LuaBinding::sol_state();
    title_=sol_state["Config"]["title"];
    data_path_=sol_state["Config"]["data_path"];
}

void ApplicationBase::Run() {
    LuaBinding::RunLuaFile("./lua/main.lua");
    //调用lua main()
    LuaBinding::CallLuaFunction("main");
}

void ApplicationBase::Update(){
    EASY_FUNCTION(profiler::colors::Magenta) // 标记函数
    Time::Update();
    UpdateScreenSize();

    GameObject::Foreach([](GameObject* game_object){
        if(game_object->active()){
            game_object->ForeachComponent([](Component* component){
                component->Update();
            });
        }
    });

    Input::Update();
    Audio::Update();
}


void ApplicationBase::Render(){
    EASY_FUNCTION(profiler::colors::Magenta); // 标记函数
    //遍历所有相机，每个相机的View Projection，都用来做一次渲染。
    Camera::Foreach([&](){
        GameObject::Foreach([](GameObject* game_object){
            if(game_object->active()==false){
                return;
            }
            MeshRenderer* mesh_renderer=game_object->GetComponent<MeshRenderer>();
            if(mesh_renderer== nullptr){
                return;
            }
            mesh_renderer->Render();
        });
    });
}

void ApplicationBase::OneFrame() {
    Update();
    Render();
    //发出特殊任务：渲染结束
    RenderTaskProducer::ProduceRenderTaskEndFrame();
}

void ApplicationBase::UpdateScreenSize() {
    RenderTaskProducer::ProduceRenderTaskUpdateScreenSize();
}

void ApplicationBase::Exit() {
    RenderTaskConsumer::Exit();
}