---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by captain.
--- DateTime: 5/16/2022 10:55 PM
---

require("lua_extension")
require("cpp_class")

--- @class Texture2D 2D纹理
Texture2D=class("Texture2D",CppClass)

function Texture2D:ctor_with(cpp_class_instance,...)
    Texture2D.super.ctor_with(self,cpp_class_instance,...)
end

--- 加载一个图片文件
--- @param image_file_path string 图片文件路径
--- @return Texture2D
function Texture2D.LoadFromFile(image_file_path)
    local cpp_instance = Cpp.Texture2D.LoadFromFile(image_file_path)
    local texture_2d=Texture2D.new_with(cpp_instance)
    return texture_2d
end

--- 返回图片宽
--- @return number
function Texture2D:width()
    return self.cpp_class_instance_:width()
end

--- 返回图片高
--- @return number
function Texture2D:height()
    return self.cpp_class_instance_:height()
end