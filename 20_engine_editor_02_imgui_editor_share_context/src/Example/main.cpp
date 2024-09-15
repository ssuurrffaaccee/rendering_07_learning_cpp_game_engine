

#define GLFW_INCLUDE_NONE

#include "Engine/App/Application.hpp"
#include "Engine/App/Application_Editor.hpp"

int main(void){
    Application::Init(new ApplicationEditor());
    Application::Run();
    return 0;
}