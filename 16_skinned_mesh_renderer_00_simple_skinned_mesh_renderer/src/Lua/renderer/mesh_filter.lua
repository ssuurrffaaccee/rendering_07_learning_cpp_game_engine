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

--- 创建Mesh
--- @param vertex_data table 所有的顶点数据,以float数组形式
--- @param vertex_index_data table 所有的索引数据,以unsigned short数组形式
function MeshFilter:CreateMesh(vertex_data,vertex_index_data)
    self.cpp_component_instance_:CreateMesh(sol2.convert_sequence_float(vertex_data),sol2.convert_sequence_ushort(vertex_index_data))
end

function MeshFilter:set_vertex_relate_bone_index_vec(vertex_relate_bone_index_vec)
    self.cpp_component_instance_:set_vertex_relate_bone_index_vec(sol2.convert_sequence_uchar(vertex_relate_bone_index_vec))
end