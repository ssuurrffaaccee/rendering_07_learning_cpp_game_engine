#pragma once
/// 渲染命令
enum RenderCommand {
    NONE,
    COMPILE_SHADER,//编译着色器
    CREATE_VAO,//创建缓冲区
    DRAW_ARRAY,//绘制
    END_FRAME,//帧结束
};