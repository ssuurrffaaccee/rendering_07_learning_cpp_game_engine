#include "Renderer.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "VertexData.hpp"
#include "ShaderSource.hpp"

Renderer::Renderer(GLFWwindow *window):window_(window) {
    render_thread_ = std::thread(&Renderer::RenderMain, this);//创建渲染线程，并指定渲染函数入口。
    render_thread_.detach();
}

Renderer::~Renderer() {
    if (render_thread_.joinable()) {
        render_thread_.join();//等待渲染线程结束
    }
}

GLuint vertex_shader, fragment_shader, program;
GLint vpos_location, vcol_location;
GLuint vbo_pos,vbo_color, vao;


/// 编译、链接Shader
void compile_shader()
{
    //创建顶点Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);
    //获取编译结果
    GLint compile_status=GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), 0, message);
        std::cout<<"compile vs error:"<<message<<std::endl;
    }

    //创建片段Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);
    //获取编译结果
    compile_status=GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), 0, message);
        std::cout<<"compile fs error:"<<message<<std::endl;
    }


    //创建GPU程序
    program = glCreateProgram();
    //附加Shader
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    //Link
    glLinkProgram(program);
    //获取编译结果
    GLint link_status=GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program, sizeof(message), 0, message);
        std::cout<<"link error:"<<message<<std::endl;
    }
}


/// 创建缓冲区
void create_buffer(){
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo_pos);
    glGenBuffers(1, &vbo_color);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kPositions), kPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(vpos_location);//启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联

    glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kColors), kColors, GL_STATIC_DRAW);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, false, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(vcol_location);//启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::RenderMain() {
    //渲染相关的API调用需要放到渲染线程中。
    glfwMakeContextCurrent(window_);

    // gladLoadGL(glfwGetProcAddress);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    compile_shader();

    //获取shader属性ID
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");

    create_buffer();

    while (!glfwWindowShouldClose(window_))
    {
        float ratio;
        int width, height;
        glm::mat4 model,view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window_, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glClearColor(49.f/255,77.f/255,121.f/255,1.f);

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program);
        {
            glBindVertexArray(vao);

            //上传顶点数据并进行绘制
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glfwSwapBuffers(window_);
    }
}