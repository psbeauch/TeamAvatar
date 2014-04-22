#include "Globals.hpp"
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameObject.hpp"
#endif

extern bool W_key, A_key, S_key, D_key, UP_key, LEFT_key, DOWN_key, RIGHT_key;

/* Keyboard controls */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);