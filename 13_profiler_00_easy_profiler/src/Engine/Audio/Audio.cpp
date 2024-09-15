#include "Engine/Audio/Audio.hpp"

#ifdef USE_FMOD_STUDIO
#include "Engine/Audio/Studio/AudioStudio.hpp"
#define AudioSolution AudioStudio
#else
#include "Engine/Audio/Core/AudioCore.hpp"
#define AudioSolution AudioCore
#endif

void Audio::Init() { AudioSolution::Init(); }

void Audio::Update() { AudioSolution::Update(); }
