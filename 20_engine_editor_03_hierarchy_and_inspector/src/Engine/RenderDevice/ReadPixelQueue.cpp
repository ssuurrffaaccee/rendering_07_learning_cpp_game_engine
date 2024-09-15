#include "Engine/RenderDevice/ReadPixelQueue.hpp"

rigtorp::SPSCQueue<ReadPixelsBuffer*> ReadPixelsQueue::read_pixels_queue_(1024);//渲染任务队列