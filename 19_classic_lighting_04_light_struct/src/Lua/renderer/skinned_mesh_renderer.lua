require("lua_extension")

--- 骨骼蒙皮动画渲染器
--- @class SkinnedMeshRenderer : MeshRenderer
SkinnedMeshRenderer=class("SkinnedMeshRenderer",MeshRenderer)

function SkinnedMeshRenderer:ctor()
    SkinnedMeshRenderer.super.ctor(self)
end

function SkinnedMeshRenderer:InitCppComponent()
    ---@type Cpp.SkinnedMeshRenderer
    self.cpp_component_instance_=Cpp.SkinnedMeshRenderer() --创建对应的C++实例
end

function SkinnedMeshRenderer:Update()
    SkinnedMeshRenderer.super.Update(self)
end