#include "Engine/Renderer/Texture2D.hpp"

#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Engine/App/Application.hpp"
#include "Engine/Utils/Debug.hpp"
#include "Engine/Utils/TimeRecorder.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"
#include "Engine/RenderDevice/GPUResourceMapper.hpp"

using std::ifstream;
using std::ios;

Texture2D::Texture2D()
    : mipmap_level_(0),
      width_(0),
      height_(0),
      gl_texture_format_(0),
      texture_handle_(0) {}

Texture2D::~Texture2D() {
  if(texture_handle_ > 0){
    RenderTaskProducer::ProduceRenderTaskDeleteTextures(1,&texture_handle_);
  }
}

void Texture2D::UpdateSubImage(int x, int y, int width, int height,
                               unsigned int client_format,
                               unsigned int data_type, unsigned char* data,unsigned int data_size) {
  if (width <= 0 || height <= 0) {
    return;
  }
  RenderTaskProducer::ProduceRenderTaskUpdateTextureSubImage2D(texture_handle_, x, y, width, height, client_format, data_type, data, data_size);
}

Texture2D* Texture2D::LoadFromFile(const std::string& image_file_path) {
  if (image_file_path.empty()) {
    DEBUG_LOG_WARN("image_file_path empty {}",image_file_path);
    return nullptr;
  }
  Texture2D* texture2d = new Texture2D();
  CptFileHead cpt_file_head;
  unsigned char* data = nullptr;
  {
    TimeRecorder time_record{"load_image_compressed"};  // 读取 cpt 压缩纹理文件
    ifstream input_file_stream(Application::data_path() + image_file_path,
                               ios::in | ios::binary);

    input_file_stream.read((char*)&cpt_file_head, sizeof(CptFileHead));
    data = (unsigned char*)malloc(cpt_file_head.compress_size_);
    input_file_stream.read((char*)data, cpt_file_head.compress_size_);
    input_file_stream.close();
  }

  texture2d->gl_texture_format_ = cpt_file_head.gl_texture_format_;
  texture2d->width_ = cpt_file_head.width_;
  texture2d->height_ = cpt_file_head.height_;
  texture2d->texture_handle_=GPUResourceMapper::GenerateTextureHandle();

  // 发出任务：创建压缩纹理
  RenderTaskProducer::ProduceRenderTaskCreateCompressedTexImage2D(texture2d->texture_handle_, texture2d->width_,
                                                                    texture2d->height_, texture2d->gl_texture_format_,
                                                                    cpt_file_head.compress_size_, data);

  delete (data);
  return texture2d;
}

Texture2D *Texture2D::Create(unsigned short width, unsigned short height, unsigned int server_format,unsigned int client_format,
                             unsigned int data_type,unsigned char* data,unsigned int data_size) {
    Texture2D* texture2d=new Texture2D();
    texture2d->gl_texture_format_=server_format;
    texture2d->width_=width;
    texture2d->height_=height;
    texture2d->texture_handle_=GPUResourceMapper::GenerateTextureHandle();

    // 发出任务：创建纹理
    RenderTaskProducer::ProduceRenderTaskCreateTexImage2D(texture2d->texture_handle_,texture2d->width_, texture2d->height_,texture2d->gl_texture_format_,client_format, data_type,data_size,data);

    return texture2d;
}