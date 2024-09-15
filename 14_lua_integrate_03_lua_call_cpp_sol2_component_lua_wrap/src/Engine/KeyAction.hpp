
#pragma once
enum class KeyAction { UP = 0, DOWN = 1, REPEAT = 2 };

KeyAction GetKeyActionUp() { return KeyAction::UP; }

KeyAction GetKeyActionDown() { return KeyAction::DOWN; }
