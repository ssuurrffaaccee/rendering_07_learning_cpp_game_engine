require("lua_extension")
require("cpp_class")

--- @class RenderTexture 渲染到纹理
RenderTexture=class("RenderTexture",CppClass)

function RenderTexture:ctor()
    RenderTexture.super.ctor(self)
    ---@field color_texture_2d_ Texture2D
    self.color_texture_2d_=nil
end

--- 实例化C++ Class
function RenderTexture:InitCppClass()
    self.cpp_class_instance_=Cpp.RenderTexture()
end

--- 初始化RenderTexture，在GPU生成帧缓冲区对象(FrameBufferObject)
--- @param width number @宽
--- @param height number @高
function RenderTexture:Init(width,height)
    self.cpp_class_instance_:Init(width,height)
end

function RenderTexture:width()
    return self.cpp_class_instance_:width()
end

function RenderTexture:set_width(width)
    return self.cpp_class_instance_:set_width(width)
end

function RenderTexture:height()
    return self.cpp_class_instance_:height()
end

function RenderTexture:set_height(height)
    return self.cpp_class_instance_:set_height(height)
end

function RenderTexture:frame_buffer_object_handle()
    return self.cpp_class_instance_:frame_buffer_object_handle()
end

function RenderTexture:in_use()
    return self.cpp_class_instance_:in_use()
end

function RenderTexture:set_in_use(in_use)
    return self.cpp_class_instance_:set_in_use(in_use)
end

function RenderTexture:color_texture_2d()
    if self.color_texture_2d_==nil then
        local cpp_color_texture_2d=self.cpp_class_instance_:color_texture_2d()
        self.color_texture_2d_=Texture2D.new_with(cpp_color_texture_2d)
    end
    return self.color_texture_2d_
end

function RenderTexture:depth_texture_2d()
    return self.cpp_class_instance_:depth_texture_2d()
end
