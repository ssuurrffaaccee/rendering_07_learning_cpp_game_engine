#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Engine/Component/Component.hpp"

class MeshFilter : public Component {
 public:
  MeshFilter();
  ~MeshFilter();
 public:
  // 顶点
  struct Vertex {
    glm::vec3 position_;
    glm::vec4 color_;
    glm::vec2 uv_;
  };

  // Mesh文件头
  struct MeshFileHead {
    char type_[4];
    unsigned short vertex_num_;        // 顶点个数
    unsigned short vertex_index_num_;  // 索引个数
  };

    //Mesh数据
    struct Mesh{
        unsigned short vertex_num_;//顶点个数
        unsigned short vertex_index_num_;//索引个数
        Vertex* vertex_data_;//顶点数据
        unsigned short* vertex_index_data_;//顶点索引数据

        Mesh(){
            vertex_num_ = 0;
            vertex_index_num_ = 0;
            vertex_data_ = nullptr;
            vertex_index_data_ = nullptr;
        }

        ~Mesh(){
            if(vertex_data_!= nullptr){
                delete[] vertex_data_;
                vertex_data_ = nullptr;
            }
            if(vertex_index_data_!= nullptr){
                delete[] vertex_index_data_;
                vertex_index_data_ = nullptr;
            }
        }

        /// 获取字节数
        unsigned short size(){
            auto total_bytes_=sizeof(vertex_num_)+vertex_num_*sizeof(Vertex)+sizeof(vertex_index_num_)+vertex_index_num_*sizeof(unsigned short);
            return total_bytes_;
        }
    };

    /// 加载Mesh文件
    /// \param mesh_file_path
    void LoadMesh(const std::string& mesh_file_path);
    /// 创建 Mesh
    /// \param vertex_data 顶点数据
    /// \param vertex_index_data 索引数据
    void CreateMesh(std::vector<Vertex>& vertex_data,std::vector<unsigned short>& vertex_index_data);

    /// 创建Mesh
    /// \param vertex_data 所有的顶点数据,以float数组形式从lua传过来
    /// \param vertex_index_data 所有的索引数据,以unsigned short数组形式从lua传过来
    void CreateMesh(std::vector<float>& vertex_data,std::vector<unsigned short>& vertex_index_data);

    /// 获取Mesh对象指针
    Mesh* mesh(){return mesh_;};

    /// 获取顶点关联骨骼索引数组，长度为顶点个数
    std::vector<unsigned char>& vertex_relate_bone_index_vec(){return vertex_relate_bone_index_vec_;};

    void set_vertex_relate_bone_index_vec(std::vector<unsigned char>& vertex_relate_bone_index_vec){
        vertex_relate_bone_index_vec_ = vertex_relate_bone_index_vec;
    }

    /// 获取蒙皮Mesh对象指针
    Mesh* skinned_mesh(){return skinned_mesh_;};
    void set_skinned_mesh(Mesh* skinned_mesh){skinned_mesh_ = skinned_mesh;};
private:
    Mesh* mesh_= nullptr;//Mesh对象
    Mesh* skinned_mesh_= nullptr;//蒙皮Mesh对象
    std::vector<unsigned char> vertex_relate_bone_index_vec_;//顶点关联骨骼索引，长度为顶点个数
  RTTR_ENABLE(Component);
};