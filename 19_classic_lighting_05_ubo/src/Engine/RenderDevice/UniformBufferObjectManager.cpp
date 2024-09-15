#include "Engine/RenderDevice/UniformBufferObjectManager.hpp"
#include <glad/glad.h>
#include "Engine/Utils/Debug.hpp"
#include "Engine/RenderDevice/RenderTaskType.hpp"
#include "Engine/RenderDevice/RenderTaskQueue.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"

std::vector<UniformBlockInstanceBindingInfo> UniformBufferObjectManager::kUniformBlockInstanceBindingInfoArray={
        {"u_ambient","AmbientBlock",16,0,0},
        {"u_light","LightBlock",32,1,0}
};

std::unordered_map<std::string,UniformBlock> UniformBufferObjectManager::kUniformBlockMap={
        {"AmbientBlock",{
            {
                    {"data.color",0,sizeof(glm::vec3)},
                    {"data.intensity",12,sizeof(float)}
                }
         }},
         {"LightBlock",{
                {
                        {"data.pos",0,sizeof(glm::vec3)},
                        {"data.color",16,sizeof(glm::vec3)},
                        {"data.intensity",28,sizeof(float)}
                }
         }}
};

void UniformBufferObjectManager::CreateUniformBufferObject(){
    for (int i = 0; i < kUniformBlockInstanceBindingInfoArray.size(); ++i) {
        UniformBlockInstanceBindingInfo& uniform_block_binding_info=kUniformBlockInstanceBindingInfoArray[i];
        glGenBuffers(1, &uniform_block_binding_info.uniform_buffer_object_);__CHECK_GL_ERROR__
        glBindBuffer(GL_UNIFORM_BUFFER, uniform_block_binding_info.uniform_buffer_object_);__CHECK_GL_ERROR__
        //先不填数据
        unsigned short uniform_block_data_size=uniform_block_binding_info.uniform_block_size_;
        glBufferData(GL_UNIFORM_BUFFER, uniform_block_data_size, NULL, GL_STATIC_DRAW);__CHECK_GL_ERROR__

        //串联 UBO 和 binding point 绑定
        glBindBufferBase(GL_UNIFORM_BUFFER, uniform_block_binding_info.binding_point_, uniform_block_binding_info.uniform_buffer_object_);__CHECK_GL_ERROR__

        glBindBuffer(GL_UNIFORM_BUFFER, 0);__CHECK_GL_ERROR__
    }
}

void UniformBufferObjectManager::UpdateUniformBlockSubData1f(std::string uniform_block_name, std::string uniform_block_member_name, float value){
    void* data= malloc(sizeof(float));
    memcpy(data,&value,sizeof(float));
    RenderTaskProducer::ProduceRenderTaskUpdateUBOSubData(uniform_block_name,uniform_block_member_name,data);
}

void UniformBufferObjectManager::UpdateUniformBlockSubData3f(std::string uniform_block_name, std::string uniform_block_member_name, glm::vec3& value){
    void* data= malloc(sizeof(glm::vec3));
    memcpy(data,&value,sizeof(glm::vec3));
    RenderTaskProducer::ProduceRenderTaskUpdateUBOSubData(uniform_block_name,uniform_block_member_name,data);
}