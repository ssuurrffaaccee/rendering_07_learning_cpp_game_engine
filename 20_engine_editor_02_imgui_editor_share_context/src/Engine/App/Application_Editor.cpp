#include "Engine/App/Application_Editor.hpp"
#include <memory>
#include <iostream>
#include "rttr/registration"
#include "easy/profiler.h"

#include "glad/glad.h"

#ifdef WIN32
// 避免出现APIENTRY重定义警告。
// freetype引用了windows.h，里面定义了APIENTRY。
// glfw3.h会判断是否APIENTRY已经定义然后再定义一次。
// 但是从编译顺序来看glfw3.h在freetype之前被引用了，判断不到 Windows.h中的定义，所以会出现重定义。
// 所以在 glfw3.h之前必须引用  Windows.h。
#include <Windows.h>
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Engine/Control/Input.hpp"
#include "Engine/Utils/Screen.hpp"
#include "Engine/Component/GameObject.hpp"
#include "Engine/Control/Input.hpp"
#include "Engine/RenderDevice/RenderDevice_OpenGL.hpp"
#include "Engine/Renderer/Camera.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Shader.hpp"
#include "Engine/Utils/Debug.hpp"
#include "Engine/RenderDevice/RenderTaskConsumer.hpp"
#include "Engine/RenderDevice/RenderTaskConsumer_Editor.hpp"
#include "Engine/RenderDevice/ReadPixelQueue.hpp"
#include "Engine/Audio/Audio.hpp"
#include "Engine/Utils/Time.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"
#include "Engine/App/Application.hpp"
#include "Engine/App/LoadTextureFromFile.hpp"

static void glfw_error_callback(int error, const char* description)
{
    DEBUG_LOG_ERROR("glfw error:{} description:{}",error,description);
}

void ApplicationEditor::InitGraphicsLibraryFramework() {
    //创建编辑器窗口
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        DEBUG_LOG_ERROR("glfw init failed!");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //创建游戏窗口
    game_glfw_window_ = glfwCreateWindow(960, 640, title_.c_str(), NULL, NULL);
    if (!game_glfw_window_)
    {
        DEBUG_LOG_ERROR("glfwCreateWindow error!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //创建编辑器窗口，并将游戏Context共享。
    editor_glfw_window_ = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, game_glfw_window_);
    if (!editor_glfw_window_)
    {
        DEBUG_LOG_ERROR("glfwCreateWindow error!");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    //设置编辑器主线程使用的是 Editor Context
    glfwMakeContextCurrent(editor_glfw_window_);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(editor_glfw_window_, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

    //初始化渲染任务消费者(单独渲染线程)
    RenderTaskConsumer::Init(new RenderTaskConsumerEditor(game_glfw_window_));
}

void ApplicationEditor::Run() {
    ApplicationBase::Run();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(editor_glfw_window_))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //1.游戏渲染画面 窗口
        {
            ImGui::Begin("Game");

            RenderTaskConsumerEditor* render_task_consumer_editor= dynamic_cast<RenderTaskConsumerEditor *>(RenderTaskConsumer::Instance());

            //从游戏渲染线程拿到FBO Attach Texture id
            GLuint texture_id=render_task_consumer_editor->color_texture_id();
            ImTextureID image_id = (void*)(intptr_t)texture_id;

            // ImGui绘制Image，使用FBO Attach Texture id
            // 第一个参数：生成的纹理的id
            // 第2个参数：Image的大小
            // 第3，4个参数：UV的起点坐标和终点坐标，UV是被规范化到（0，1）之间的坐标
            // 第5个参数：图片的色调
            // 第6个参数：图片边框的颜色
            ImGui::Image(image_id, ImVec2(480,320), ImVec2(0.0, 1.0), ImVec2(1.0, 0.0), ImVec4(1, 1, 1, 1), ImVec4(0, 1, 0, 1));

            ImGui::End();
        }

        //2.游戏渲染深度图 窗口
        {
            ImGui::Begin("Depth");

            RenderTaskConsumerEditor* render_task_consumer_editor= dynamic_cast<RenderTaskConsumerEditor *>(RenderTaskConsumer::Instance());

            GLuint texture_id=render_task_consumer_editor->depth_texture_id();
            ImTextureID image_id = (void*)(intptr_t)texture_id;

            ImGui::Image(image_id, ImVec2(480,320), ImVec2(0.0, 1.0), ImVec2(1.0, 0.0), ImVec4(1, 1, 1, 1), ImVec4(0, 1, 0, 1));

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(editor_glfw_window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(editor_glfw_window_);

        //渲染游戏
        EASY_BLOCK("Frame"){
            OneFrame();
        }EASY_END_BLOCK;
    }

    Exit();
}

void ApplicationEditor::Exit() {
    ApplicationBase::Exit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(editor_glfw_window_);
    glfwDestroyWindow(game_glfw_window_);
    glfwTerminate();
}