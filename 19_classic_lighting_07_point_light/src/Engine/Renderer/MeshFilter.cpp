#include "Engine/Renderer/MeshFilter.hpp"

#include <fstream>
#include <rttr/registration>

#include "Engine/Utils/Application.hpp"

using namespace rttr;
RTTR_REGISTRATION {
  registration::class_<MeshFilter>("MeshFilter")
      .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}
MeshFilter::MeshFilter() : mesh_(nullptr),skinned_mesh_{nullptr} {}

void MeshFilter::LoadMesh(const std::string &mesh_file_path) {
    //读取 Mesh文件头
    std::ifstream input_file_stream(Application::data_path()+mesh_file_path,std::ios::in | std::ios::binary);
    MeshFileHead mesh_file_head;
    input_file_stream.read((char*)&mesh_file_head,sizeof(mesh_file_head));
    //读取顶点数据
    unsigned char* vertex_data =(unsigned char*)malloc(mesh_file_head.vertex_num_*sizeof(Vertex));
    input_file_stream.read((char*)vertex_data,mesh_file_head.vertex_num_*sizeof(Vertex));
    //读取顶点索引数据
    unsigned short* vertex_index_data=(unsigned short*)malloc(mesh_file_head.vertex_index_num_*sizeof(unsigned short));
    input_file_stream.read((char*)vertex_index_data,mesh_file_head.vertex_index_num_*sizeof(unsigned short));
    input_file_stream.close();

    mesh_=new Mesh();
    mesh_->name_=mesh_file_head.name_;
    mesh_->vertex_num_=mesh_file_head.vertex_num_;
    mesh_->vertex_index_num_=mesh_file_head.vertex_index_num_;
    mesh_->vertex_data_=(Vertex*)vertex_data;
    mesh_->vertex_index_data_=vertex_index_data;
}

MeshFilter::~MeshFilter() {
    if(mesh_!=nullptr) {
        delete mesh_;
        mesh_=nullptr;
    }
    if(skinned_mesh_!=nullptr) {
        delete skinned_mesh_;
        skinned_mesh_=nullptr;
    }
    if(vertex_relate_bone_infos_!=nullptr) {
        delete [] vertex_relate_bone_infos_;
        vertex_relate_bone_infos_=nullptr;
    }
}

void MeshFilter::CreateMesh(std::vector<Vertex> &vertex_data, std::vector<unsigned short> &vertex_index_data) {
    if(mesh_!= nullptr){
        delete mesh_;
        mesh_=nullptr;
    }
    mesh_=new Mesh();
    mesh_->vertex_num_=vertex_data.size();
    mesh_->vertex_index_num_=vertex_index_data.size();

    unsigned short vertex_data_size= mesh_->vertex_num_ * sizeof(Vertex);
    mesh_->vertex_data_= static_cast<Vertex *>(malloc(vertex_data_size));
    memcpy(mesh_->vertex_data_, &vertex_data[0], vertex_data_size);

    unsigned short vertex_index_data_size=mesh_->vertex_num_ * sizeof(Vertex);
    mesh_->vertex_index_data_= static_cast<unsigned short *>(malloc(vertex_index_data_size));
    memcpy(mesh_->vertex_index_data_,&vertex_index_data[0],vertex_index_data_size);
}

void MeshFilter::CreateMesh(std::vector<float>& vertex_data,std::vector<unsigned short>& vertex_index_data){
    if(mesh_!= nullptr){
        delete mesh_;
        mesh_=nullptr;
    }
    mesh_=new Mesh();
    mesh_->vertex_num_=vertex_data.size()/9;//一个vertex由9个float组成。
    mesh_->vertex_index_num_=vertex_index_data.size();

    unsigned short vertex_data_size= mesh_->vertex_num_ * sizeof(Vertex);
    mesh_->vertex_data_= static_cast<Vertex *>(malloc(vertex_data_size));
    memcpy(mesh_->vertex_data_, &vertex_data[0], vertex_data_size);

    unsigned short vertex_index_data_size=mesh_->vertex_index_num_ * sizeof(unsigned short);
    mesh_->vertex_index_data_= static_cast<unsigned short *>(malloc(vertex_index_data_size));
    memcpy(mesh_->vertex_index_data_,&vertex_index_data[0],vertex_index_data_size);
}

const char* MeshFilter::GetMeshName() {
    return mesh_->name_;
}

void MeshFilter::LoadWeight(std::string weight_file_path) {
    //读取 Mesh文件头
    std::ifstream input_file_stream(Application::data_path()+weight_file_path,std::ios::in | std::ios::binary);
    if (!input_file_stream.is_open()){
        DEBUG_LOG_ERROR("weight file open failed");
        return;
    }
    //判断文件头
    char file_head[7];
    input_file_stream.read(file_head,6);
    file_head[6]='\0';
    if(strcmp(file_head,"weight") != 0) {
        DEBUG_LOG_ERROR("weight file head error");
        return;
    }
    //读取权重数据
    input_file_stream.seekg(0,std::ios::end);
    int length = input_file_stream.tellg();
    input_file_stream.seekg(6,std::ios::beg);
    vertex_relate_bone_infos_ =(VertexRelateBoneInfo*)malloc(length-6);
    input_file_stream.read((char*)vertex_relate_bone_infos_,length-6);
    //关闭文件
    input_file_stream.close();
}