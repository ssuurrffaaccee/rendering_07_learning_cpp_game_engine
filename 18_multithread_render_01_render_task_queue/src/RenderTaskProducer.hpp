#pragma once
#include <glad/glad.h>
/// 渲染任务生产者
class RenderTaskProducer {
public:
    /// 发出阻塞型任务：编译Shader
    /// \param vertex_shader_source 顶点shader源码
    /// \param fragment_shader_source 片段shader源码
    /// \param result_shader_program_id 回传的Shader程序ID
    static void ProduceRenderTaskCompileShader(const char* vertex_shader_source,const char* fragment_shader_source,GLuint& result_shader_program_id);

    /// 发出任务：创建VAO
    /// \param shader_program_id 使用的Shader程序ID
    /// \param positions 绘制的顶点位置
    /// \param positions_stride 顶点位置数组的stride
    /// \param colors 绘制的顶点颜色
    /// \param colors_stride 顶点颜色数组的stride
    /// \param result_vao 回传的VAO
    static void ProduceRenderTaskCreateVAO(GLuint shader_program_id, const void* positions, GLsizei positions_stride, const void* colors, GLsizei colors_stride, GLuint& result_vao);

    /// 发出任务：绘制
    /// \param shader_program_id 使用的Shader程序ID
    /// \param vao
    static void ProduceRenderTaskDrawArray(GLuint shader_program_id, GLuint vao);

    /// 发出特殊任务：渲染结束
    static void ProduceRenderTaskEndFrame();
};