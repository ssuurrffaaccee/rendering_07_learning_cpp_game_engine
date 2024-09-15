#pragma once
class RenderTaskConsumerBase;

/// 渲染任务消费端
class RenderTaskConsumer {
public:
    static void Init(RenderTaskConsumerBase* instance);

    static RenderTaskConsumerBase* Instance();

    static void Exit();
private:
    static RenderTaskConsumerBase* instance_;
};


