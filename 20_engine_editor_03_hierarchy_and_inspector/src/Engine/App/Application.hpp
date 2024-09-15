#pragma once
#include <string>

class ApplicationBase;
class Application {
public:
    static void Init(ApplicationBase* instance);

    static const std::string& data_path();

    static void Run();
private:
    static ApplicationBase* instance_;
};
