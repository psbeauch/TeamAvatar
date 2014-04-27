#include "Keyboard.hpp"
#include <stdio.h>

bool W_key = false, A_key = false, S_key = false, D_key = false, UP_key = false, LEFT_key = false, DOWN_key = false, RIGHT_key = false;

void setKey(bool *key, int action) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		*key = true;
	}
	else if (action == GLFW_RELEASE) {
		*key = false;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//printf("Key pressed: %c\n", key);
		/* manual camera movement */
		switch (key) {
			/*
			case GLFW_KEY_W:
				eye.z += 0.1f;
				lookAt.z += 0.1f;
				break;
			case GLFW_KEY_S:
				eye.z -= 0.1f;
				lookAt.z -= 0.1f;
				break;
			case GLFW_KEY_A:
				eye.x += 0.1f;
				lookAt.x += 0.1f;
				break;
			case GLFW_KEY_D:
				eye.x -= 0.1f;
				lookAt.x -= 0.1f;
				break;
			*/
			/* player 1 controls  */
			
			case GLFW_KEY_W:
				setKey(&W_key, action);
				break;
			case GLFW_KEY_A:
				setKey(&A_key, action);
				break;
			case GLFW_KEY_S:
				setKey(&S_key, action);
				break;
			case GLFW_KEY_D:
				setKey(&D_key, action);
				break;
			case GLFW_KEY_UP:
				setKey(&UP_key, action);
				break;
			case GLFW_KEY_LEFT:
				setKey(&LEFT_key, action);
				break;
			case GLFW_KEY_DOWN:
				setKey(&DOWN_key, action);
				break;
			case GLFW_KEY_RIGHT:
				setKey(&RIGHT_key, action);
				break;
				
		}
}

