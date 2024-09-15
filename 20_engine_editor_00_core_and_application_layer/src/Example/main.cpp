

#define GLFW_INCLUDE_NONE

#include "Engine/App/Application.hpp"
#include "Engine/App/Application_Standalone.hpp"

int main(void){
    Application::Init(new ApplicationStandalone());
    Application::Run();
    return 0;
}
