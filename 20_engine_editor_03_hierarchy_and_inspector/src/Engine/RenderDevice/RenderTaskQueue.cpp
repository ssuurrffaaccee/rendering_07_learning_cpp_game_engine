#include "Engine/RenderDevice/RenderTaskQueue.hpp"

rigtorp::SPSCQueue<RenderTaskBase*> RenderTaskQueue::render_task_queue_(1024);//渲染任务队列