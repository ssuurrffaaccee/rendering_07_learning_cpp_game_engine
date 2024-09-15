#include "Engine/RenderDevice/GPUResourceMapper.hpp"

unsigned int GPUResourceMapper::shader_program_index_=0;//Shader程序索引
unsigned int GPUResourceMapper::vao_index_=0;//VAO索引
unsigned int GPUResourceMapper::vbo_index_=0;//VBO索引
unsigned int GPUResourceMapper::texture_index_=0;//Texture索引
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::shader_program_map_;//Shader程序映射表
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::vao_map_;//VAO映射表
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::vbo_map_;//VBO映射表
std::unordered_map<unsigned int, GLuint> GPUResourceMapper::texture_map_;//Texture映射表
