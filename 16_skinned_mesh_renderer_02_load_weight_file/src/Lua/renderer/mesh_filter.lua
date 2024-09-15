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

--- 设置顶点关联骨骼信息
--- @param vertex_relate_bone_info_data table unsigned char数组形式，长度为顶点个数*8.
function MeshFilter:set_vertex_relate_bone_infos(vertex_relate_bone_info_data)
    self.cpp_component_instance_:set_vertex_relate_bone_infos(sol2.convert_sequence_int(vertex_relate_bone_info_data))
end

--- 加载权重文件
--- @param weight_file_path string @权重文件路径
function MeshFilter:LoadWeight(weight_file_path)
    self.cpp_component_instance_:LoadWeight(weight_file_path)
end