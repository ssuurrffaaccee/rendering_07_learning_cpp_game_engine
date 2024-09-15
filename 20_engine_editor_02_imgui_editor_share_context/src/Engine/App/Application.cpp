
#include "Engine/App/Application.hpp"
#include "Engine/App/ApplicationBase.hpp"

ApplicationBase* Application::instance_= nullptr;

void Application::Init(ApplicationBase* instance) {
    instance_=instance;
    instance_->Init();
}

const std::string& Application::data_path() {
    return instance_->data_path();
}

void Application::Run() {
    instance_->Run();
}