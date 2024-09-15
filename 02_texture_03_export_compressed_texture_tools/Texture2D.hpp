#pragma once

#include <glad/glad.h>
#include <GL/glext.h>
#include <iostream>

class Texture2D {
private:
  Texture2D()
      : mipmap_level_(0) {

        };
  ~Texture2D() {};

public:
  static Texture2D *
  LoadFromFile(std::string &image_file_path); // 加载一个图片文件

  static void CompressImageFile(
      std::string &image_file_path,
      std::string &
          save_image_file_path); // 从GPU中，将显存中保存的压缩好的纹理数据，下载到内存，并保存到硬盘。
public:
  int mipmap_level_;
  int width_;
  int height_;

  GLenum gl_texture_format_;
  GLuint gl_texture_id_; // 纹理ID

  // tcp文件头
  struct CptFileHead {
    char type_[3];
    int mipmap_level_;
    int width_;
    int height_;
    int gl_texture_format_;
    int compress_size_;
  };
};