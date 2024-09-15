require("lua_extension")

MeshFilter=class("MeshFilter",Component)

function MeshFilter:ctor()
    MeshFilter.super.ctor(self)
end

function MeshFilter:InitCppComponent()
    ---@type Cpp.MeshFilter
    self.cpp_component_instance_=Cpp.MeshFilter()
end

--- 加载Mesh文件
--- @param mesh_file_path
function MeshFilter:LoadMesh(mesh_file_path)
    self.cpp_component_instance_:LoadMesh(mesh_file_path)
end
