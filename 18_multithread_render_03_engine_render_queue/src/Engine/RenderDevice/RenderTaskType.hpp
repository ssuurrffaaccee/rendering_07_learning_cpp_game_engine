#pragma once 
#include <stdlib.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include "Engine/RenderDevice/RenderCommand.hpp"
#include "Engine/Utils/Condition.hpp"

/// 渲染任务基类
class RenderTaskBase{
public:
    RenderTaskBase(){}
    virtual ~RenderTaskBase(){}
public:
    RenderCommand render_command_{};//渲染命令
    bool need_return_result_ = false;//是否需要回传结果
    bool return_result_set_ = false;//是否设置好了回传结果
    virtual std::string GetName(){
         return "RenderTaskBase";
    }
};
#define DEFINE_GET_NAME(NAME)\
    std::string GetName() override{\
         return #NAME;\
    }  

/// 需要回传结果的阻塞性任务
class RenderTaskNeedReturnResult: public RenderTaskBase{
public:
    RenderTaskNeedReturnResult(){
        render_command_=RenderCommand::NONE;
        need_return_result_=true;
    }
    ~RenderTaskNeedReturnResult(){}
    /// 等待任务在渲染线程执行完毕，并设置回传结果。主线程拿到结果后才能执行下一步代码。
    virtual void Wait(){
        while(!flag_.Wait([this](){
            return this->return_result_set_;
        },std::chrono::microseconds(10))){ 
        };
    }
    virtual void Signal(){
        flag_.Signal([this](){
            this->return_result_set_=true;
        });
    }
    Condition flag_;
    DEFINE_GET_NAME(RenderTaskNeedReturnResult)
};

/// 更新游戏画面尺寸任务
class RenderTaskUpdateScreenSize:public RenderTaskBase{
public:
    RenderTaskUpdateScreenSize(){
        render_command_=RenderCommand::UPDATE_SCREEN_SIZE;
    }
    ~RenderTaskUpdateScreenSize(){}
    DEFINE_GET_NAME(RenderTaskUpdateScreenSize)
};

/// 编译着色器任务
class RenderTaskCompileShader: public RenderTaskBase{
public:
    RenderTaskCompileShader(){
        render_command_=RenderCommand::COMPILE_SHADER;
    }
    ~RenderTaskCompileShader(){
        free(vertex_shader_source_);
        free(fragment_shader_source_);
    }
    DEFINE_GET_NAME(RenderTaskCompileShader)
public:
    char* vertex_shader_source_= nullptr;
    char* fragment_shader_source_= nullptr;
    unsigned int shader_program_handle_= 0;
};

/// 使用着色器程序任务
class RenderTaskUseShaderProgram: public RenderTaskBase{
public:
    RenderTaskUseShaderProgram(){
        render_command_=RenderCommand::USE_SHADER_PROGRAM;
    }
    ~RenderTaskUseShaderProgram(){}
    DEFINE_GET_NAME(RenderTaskUseShaderProgram)
public:
    unsigned int shader_program_handle_= 0;
};

/// 创建压缩纹理任务
class RenderTaskCreateCompressedTexImage2D: public RenderTaskBase{
public:
    RenderTaskCreateCompressedTexImage2D(){
        render_command_=RenderCommand::CREATE_COMPRESSED_TEX_IMAGE2D;
    }
    ~RenderTaskCreateCompressedTexImage2D(){
        free(data_);
    }
    DEFINE_GET_NAME(RenderTaskCreateCompressedTexImage2D)
public:
    unsigned int texture_handle_= 0;
    int width_;
    int height_;
    unsigned int texture_format_;
    int compress_size_;
    unsigned char* data_;
};

/// 创建纹理任务
class RenderTaskCreateTexImage2D: public RenderTaskBase{
public:
    RenderTaskCreateTexImage2D(){
        render_command_=RenderCommand::CREATE_TEX_IMAGE2D;
    }
    ~RenderTaskCreateTexImage2D(){
        free(data_);
    }
    DEFINE_GET_NAME(RenderTaskCreateTexImage2D)
public:
    unsigned int texture_handle_= 0;
    int width_;
    int height_;
    unsigned int gl_texture_format_;//GL内部纹理格式
    unsigned int client_format_;//客户端纹理格式
    unsigned int data_type_;
    unsigned char* data_;
};

/// 删除Texture任务
class RenderTaskDeleteTextures: public RenderTaskBase{
public:
    RenderTaskDeleteTextures(){
        render_command_=RenderCommand::DELETE_TEXTURES;
    }
    ~RenderTaskDeleteTextures(){
        free(texture_handle_array_);
    }
    DEFINE_GET_NAME(RenderTaskDeleteTextures)
public:
    unsigned int* texture_handle_array_=nullptr;//存储纹理句柄的数组
    int texture_count_=0;//纹理数量
};

/// 局部更新Texture任务
class RenderTaskUpdateTextureSubImage2D:public RenderTaskBase{
public:
    RenderTaskUpdateTextureSubImage2D(){
        render_command_=RenderCommand::UPDATE_TEXTURE_SUB_IMAGE2D;
    }
    ~RenderTaskUpdateTextureSubImage2D(){
        free(data_);
    }
    DEFINE_GET_NAME(RenderTaskUpdateTextureSubImage2D)
public:
    unsigned int texture_handle_;//纹理句柄
    int x_,y_,width_,height_;
    unsigned int client_format_;
    unsigned int data_type_;
    unsigned char* data_;
    unsigned int data_size_;
};

/// 创建VAO任务
class RenderTaskCreateVAO: public RenderTaskBase{
public:
    RenderTaskCreateVAO(){
        render_command_=RenderCommand::CREATE_VAO;
    }
    ~RenderTaskCreateVAO(){
        free(vertex_data_);
        free(vertex_index_data_);
    }
    DEFINE_GET_NAME(RenderTaskCreateVAO)
public:
    unsigned int shader_program_handle_=0;//着色器程序句柄
    unsigned int vao_handle_=0;//VAO句柄
    unsigned int vbo_handle_=0;//VBO句柄
    unsigned int vertex_data_size_;//顶点数据大小
    unsigned int vertex_data_stride_;
    void* vertex_data_;//顶点数据
    unsigned int vertex_index_data_size_;//顶点索引数据大小
    void* vertex_index_data_;//顶点索引数据
};

/// 更新VBO数据
class RenderTaskUpdateVBOSubData:public RenderTaskBase{
public:
    RenderTaskUpdateVBOSubData(){
        render_command_=RenderCommand::UPDATE_VBO_SUB_DATA;
    }
    ~RenderTaskUpdateVBOSubData(){
        free(vertex_data_);
    }
    DEFINE_GET_NAME(RenderTaskUpdateVBOSubData)
public:
    unsigned int vbo_handle_=0;//VBO句柄
    unsigned int vertex_data_size_;//顶点数据大小
    void* vertex_data_;//顶点数据
};

/// 设置状态，开启或关闭
class RenderTaskSetEnableState: public RenderTaskBase{
public:
    RenderTaskSetEnableState(){
        render_command_=RenderCommand::SET_ENABLE_STATE;
    }
    ~RenderTaskSetEnableState(){}
    DEFINE_GET_NAME(RenderTaskSetEnableState)
public:
    unsigned int state_;//OpenGL状态
    bool enable_;//OpenGL状态值
};

/// 设置混合函数
class RenderTaskSetBlenderFunc: public RenderTaskBase{
public:
    RenderTaskSetBlenderFunc(){
        render_command_=RenderCommand::SET_BLENDER_FUNC;
    }
    ~RenderTaskSetBlenderFunc(){}
    DEFINE_GET_NAME(RenderTaskSetBlenderFunc)
public:
    unsigned int source_blending_factor_;//源混合因子
    unsigned int destination_blending_factor_;//目标混合因子
};

/// 上传4x4矩阵
class RenderTaskSetUniformMatrix4fv: public RenderTaskBase{
public:
    RenderTaskSetUniformMatrix4fv(){
        render_command_=RenderCommand::SET_UNIFORM_MATRIX_4FV;
    }
    ~RenderTaskSetUniformMatrix4fv(){
        free(uniform_name_);
    }
    DEFINE_GET_NAME(RenderTaskSetUniformMatrix4fv)
public:
    unsigned int shader_program_handle_=0;//着色器程序句柄
    char* uniform_name_= nullptr;//uniform变量名
    bool transpose_=false;//是否转置
    glm::mat4 matrix_;//4x4矩阵数据
};

/// 激活并绑定纹理
class RenderTaskActiveAndBindTexture:public RenderTaskBase{
public:
    RenderTaskActiveAndBindTexture(){
        render_command_=RenderCommand::ACTIVE_AND_BIND_TEXTURE;
    }
    ~RenderTaskActiveAndBindTexture(){}
    DEFINE_GET_NAME(RenderTaskActiveAndBindTexture)
public:
    unsigned int texture_uint_;//纹理单元
    unsigned int texture_handle_;//纹理句柄
};

/// 上传1个int值
class RenderTaskSetUniform1i:public RenderTaskBase{
public:
    RenderTaskSetUniform1i(){
        render_command_=RenderCommand::SET_UNIFORM_1I;
    }
    ~RenderTaskSetUniform1i(){
        free(uniform_name_);
    }
    DEFINE_GET_NAME(RenderTaskSetUniform1i)
public:
    unsigned int shader_program_handle_;//shader程序句柄
    char* uniform_name_=nullptr;//uniform变量名
    int value_;//目标值
};

/// 绑定VAO并绘制
class RenderTaskBindVAOAndDrawElements:public RenderTaskBase{
public:
    RenderTaskBindVAOAndDrawElements(){
        render_command_=RenderCommand::BIND_VAO_AND_DRAW_ELEMENTS;
    }
    ~RenderTaskBindVAOAndDrawElements(){}
    DEFINE_GET_NAME(RenderTaskBindVAOAndDrawElements)
public:
    unsigned int vao_handle_;
    unsigned int vertex_index_num_;//索引数量
};

/// 清除
class RenderTaskClear:public RenderTaskBase{
public:
    RenderTaskClear(){
        render_command_=RenderCommand::SET_CLEAR_FLAG_AND_CLEAR_COLOR_BUFFER;
    }
    ~RenderTaskClear(){}
    DEFINE_GET_NAME(RenderTaskClear)
public:
    unsigned int clear_flag_;
    float clear_color_r_;
    float clear_color_g_;
    float clear_color_b_;
    float clear_color_a_;
};

/// 设置模板测试函数
class RenderTaskSetStencilFunc:public RenderTaskBase{
public:
    RenderTaskSetStencilFunc(){
        render_command_=RenderCommand::SET_STENCIL_FUNC;
    }
    ~RenderTaskSetStencilFunc(){}
    DEFINE_GET_NAME(RenderTaskSetStencilFunc)
public:
    unsigned int stencil_func_;
    int stencil_ref_;
    unsigned int stencil_mask_;
};

/// 设置模板操作
class RenderTaskSetStencilOp:public RenderTaskBase{
public:
    RenderTaskSetStencilOp(){
        render_command_=RenderCommand::SET_STENCIL_OP;
    }
    ~RenderTaskSetStencilOp(){}
    DEFINE_GET_NAME(RenderTaskSetStencilOp)
public:
    unsigned int fail_op_;
    unsigned int z_test_fail_op_;
    unsigned int z_test_pass_op_;
};

/// 设置清除模板缓冲值
class RenderTaskSetStencilBufferClearValue:public RenderTaskBase{
public:
    RenderTaskSetStencilBufferClearValue(){
        render_command_=RenderCommand::SET_STENCIL_BUFFER_CLEAR_VALUE;
    }
    ~RenderTaskSetStencilBufferClearValue(){}
    DEFINE_GET_NAME(RenderTaskSetStencilBufferClearValue)
public:
    int clear_value_;
};

/// 特殊任务：帧结束标志，渲染线程收到这个任务后，刷新缓冲区，设置帧结束。
class RenderTaskEndFrame: public RenderTaskNeedReturnResult {
public:
    RenderTaskEndFrame(){
        render_command_=RenderCommand::END_FRAME;
    }
    ~RenderTaskEndFrame(){}
    DEFINE_GET_NAME(RenderTaskEndFrame)
};
#undef DEFINE_GET_NAME