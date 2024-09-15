
#include <stdio.h>
#include <stdlib.h>

#include "VertexData.hpp"

int main(void) {
  VertexRemoveDumplicate();
  // 需要手动创建 model 文件夹。
  ExportMesh("../../resources/model/cube.mesh");
  return 0;
}