require("lua_extension")
require("cpp_class")

--- @class Material 材质
Material=class("Material",CppClass)

function Material:ctor()
    Material.super.ctor(self)
end

--- 实例化C++ Class
function Material:InitCppClass()
    self.cpp_class_instance_=Cpp.Material()
end

--- 加载Material文件并解析
function Material:Parse(material_path)
    self.cpp_class_instance_:Parse(material_path)
end


function Material:SetUniformMatrix4fv(shader_property_name,pointer)
    self.cpp_class_instance_:SetUniformMatrix4fv(shader_property_name,pointer)
end

function Material:SetUniform1i(shader_property_name,value)
    self.cpp_class_instance_:SetUniform1i(shader_property_name,value)
end

--- 设置纹理
--- @param property
--- @param texture2D
function Material:SetTexture(property,texture2D)
    self.cpp_class_instance_:SetTexture(property,texture2D)
end

function Material:shader()
    return self.cpp_class_instance_:shader()
end

function Material:textures()
    return self.cpp_class_instance_:textures()
end