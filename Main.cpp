#include <stdio.h>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameObject.hpp"
#endif

#include "Keyboard.hpp"
#ifndef SIMPLE_GEOM_H
#define SIMPLE_GOEM_H
#include "SimpleGeom.hpp"
#endif

#include <vector>
#include "GLSL_helper.h"
#define MAX_PLAYERS 2

GameObject players[MAX_PLAYERS];
std::vector<GameObject> env;

/* projection matrix */
void SetProjectionMatrix() {
	glm::mat4 Projection = glm::perspective(90.0f, (float)w_width / w_height, 0.1f, 100.f);
	safe_glUniformMatrix4fv(h_uProjMatrix, glm::value_ptr(Projection));
}

/* view matrix */
void SetView() {
	glm::mat4 camera = glm::lookAt(eye, lookAt, up);
	safe_glUniformMatrix4fv(h_uViewMatrix, glm::value_ptr(camera));
}

/* main display function */
void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(ShadeProg);

	if (debug) printf("Setting matrixes\n");
	SetProjectionMatrix();
	SetView();

	//light position
	safe_glUniform3f(h_uLPos, lightPos.x, lightPos.y, lightPos.z);
	//camera position
	safe_glUniform3f(h_uCameraPos, eye.x, eye.y, eye.z);

	for (std::vector<GameObject>::iterator it = env.begin(); it != env.end(); ++it) {
		it->render();
	}

	for (int i = 0; i < MAX_PLAYERS; i++) {
		players[i].render();
	}
}

void Initialize()	// Any GL Init Code 
{
	// Start Of User Initialization
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Black Background
	glClearDepth(1.0f);	// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);// Enable Depth Testing
}

/* function to load shaders */
int InstallShader(const GLchar *vShaderName, const GLchar *fShaderName) {
	GLuint VS, FS; //handles to shader object
	GLint vCompiled, fCompiled, linked; //status of shader

	FS = glCreateShader(GL_FRAGMENT_SHADER);
	VS = glCreateShader(GL_VERTEX_SHADER);

	//load the source
	glShaderSource(VS, 1, &vShaderName, NULL);
	glShaderSource(FS, 1, &fShaderName, NULL);

	//compile shader and print log
	glCompileShader(VS);
	/* check shader status requires helper functions */
	printOpenGLError();
	glGetShaderiv(VS, GL_COMPILE_STATUS, &vCompiled);
	printShaderInfoLog(VS);

	//compile shader and print log
	glCompileShader(FS);
	/* check shader status requires helper functions */
	printOpenGLError();
	glGetShaderiv(FS, GL_COMPILE_STATUS, &fCompiled);
	printShaderInfoLog(FS);

	if (!vCompiled || !fCompiled) {
		fprintf(stderr, "Error compiling the shader %s", vShaderName);
		return 0;
	}

	//create a program object and attach the compiled shader
	ShadeProg = glCreateProgram();
	glAttachShader(ShadeProg, VS);
	glAttachShader(ShadeProg, FS);

	glLinkProgram(ShadeProg);
	/* check shader status requires helper functions */
	printOpenGLError();
	glGetProgramiv(ShadeProg, GL_LINK_STATUS, &linked);
	printProgramInfoLog(ShadeProg);

	glUseProgram(ShadeProg);
	h_aPosition = safe_glGetAttribLocation(ShadeProg, "aPosition");
	h_aNormal = safe_glGetAttribLocation(ShadeProg, "aNormal");
	h_uProjMatrix = safe_glGetUniformLocation(ShadeProg, "uProjMatrix");
	h_uViewMatrix = safe_glGetUniformLocation(ShadeProg, "uViewMatrix");
	h_uModelMatrix = safe_glGetUniformLocation(ShadeProg, "uModelMatrix");
	h_uLPos = safe_glGetUniformLocation(ShadeProg, "uLPos");
	h_uCameraPos = safe_glGetUniformLocation(ShadeProg, "cameraPos");
	h_uCol = safe_glGetUniformLocation(ShadeProg, "dColor");
	h_uOutline = safe_glGetUniformLocation(ShadeProg, "uOutline");

	printf("sucessfully installed shader %d\n", ShadeProg);
	return 1;
}

void SetupScene() {
	/* environment */
	GameObject ground = CubeObject();
	ground.scale = glm::vec3(35.0f, 1.0f, 2.0f);
	env.push_back(ground);
	GameObject platform = CubeObject();
	platform.scale = glm::vec3(4.0f, 0.15f, 2.0f);
	platform.position = glm::vec3(3.0f, 6.5f, 0.0f);
	env.push_back(platform);

	/* characters */
	GameObject p1 = CubeObject();
	p1.scale = glm::vec3(0.5f, 2.0f, 0.5f);
	p1.position = glm::vec3(-5.0f, 4.5f, 0.0f);
	players[0] = p1;

	/* test stuff for assimp */
	//p1.setupVertices("untitled.dae");

	GameObject p2 = CubeObject();
	p2.scale = glm::vec3(0.5f, 2.0f, 0.5f);
	p2.position = glm::vec3(5.0f, 4.5f, 0.0f);
	players[1] = p2;
}

void ProcessMovement() {
	/* player 1 */
	if (W_key && !S_key) {					//up
		if (players[0].velocity.y == 0.0f) {
			players[0].velocity.y = 2.5f;
			players[0].falling = true;
		}
	}
	else if (!W_key && S_key) {				//down

	}
	else {									//no vertical

	}
	if (A_key && !D_key) {					//left
		players[0].velocity.x = -1.5f;
	}
	else if (!A_key && D_key) {				//right
		players[0].velocity.x = 1.5f;
	}
	else {									//no horizontal
		players[0].velocity.x = 0.0f;
	}
	//player 1
	if (UP_key && !DOWN_key) {				//up
		if (players[1].velocity.y == 0.0f) {
			players[1].velocity.y = 2.5f;
			players[1].falling = true;
		}
	}
	else if (!UP_key && DOWN_key) {		//down

	}
	else {									//no vertical

	}
	if (LEFT_key && !RIGHT_key) {			//left
		players[1].velocity.x = -1.5f;
	}
	else if (!LEFT_key && RIGHT_key) {		//right
		players[1].velocity.x = 1.5f;
	}
	else {									//no horizontal
		players[1].velocity.x = 0.0f;
	}
}

void CameraPos() {
	glm::vec3 midpoint = eye;
	int l = 0, r = 0;
	/* find leftmost and rightmost players */
	for (int i = 1; i < MAX_PLAYERS; i++) {
		if (players[i].position.x < players[l].position.x) {
			l = i;
		}
		if (players[i].position.x > players[r].position.x) {
			r = i;
		}
	}
	midpoint.x = ((players[r].position.x - players[l].position.x) / 2) + players[l].position.x;
	if (midpoint.x < MIN_CAM_X) midpoint.x = MIN_CAM_X;
	else if (midpoint.x > MAX_CAM_X) midpoint.x = MAX_CAM_X;
	eye = midpoint;
	lookAt = eye;
	lookAt.z = 0.0f;

	float dist = players[r].position.x - players[l].position.x;
	if (dist < MIN_DIST) dist = MIN_DIST;
	else if (dist > MAX_DIST) dist = MAX_DIST;

	float ratio = (dist - MIN_DIST) / (MAX_DIST - MIN_DIST);
	printf("current ratio is: %f\n", ratio);

	eye.z = DEF_CAM_Z + (ratio * 8.0f);
}

void GameLoop(int dt) {
	ProcessMovement();
	CameraPos();
	glm::vec3 oldPos;
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (players[i].falling) {
			players[i].velocity.y -= 0.007f;
		}
		else {
			players[i].velocity.y = 0.0f;
		}
		if (players[i].velocity.y < -3.5f) {
			players[i].velocity.y = -3.5f;
		}
		oldPos = players[i].position;
		players[i].position += players[i].velocity * 0.015f;
		int col = NO_COL;
		for (std::vector<GameObject>::iterator it = env.begin(); it != env.end(); ++it) {
			col = players[i].checkCollision(*it);
			if (col != NO_COL) {
				break;
			}
		}
		if (col == LOWER_COL) {
			players[i].position = oldPos;
			players[i].falling = false;
		}
		else if (col == NO_COL) {
			players[i].falling = true;
		}
		if (players[i].position.y < -100.0f) {
			if (i < MAX_PLAYERS / 2) {
				players[i].position = playerSpawn;
				players[i].position.x -= (5.0f * i);
			}
			else {
				players[i].position = playerSpawn;
				players[i].position.x += (5.0f * i);
			}
		}
	}
}

int main() {
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// uncomment these lines if on Apple OS X
	/*glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	GLFWwindow* window = glfwCreateWindow(w_width, w_height, "Engine", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	Initialize();

	if (!InstallShader(textFileRead((char *)"vert.glsl"), textFileRead((char *)"frag.glsl"))) {
		fprintf(stderr, "Error installing shader\n");
		return 0;
	}

	SetupScene();
	int t1, t2;

	while (!glfwWindowShouldClose(window)) {
		// update other events like input handling
		GameLoop(0);
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		Render();
		glfwSwapBuffers(window);
		//printf("dt = %d\n", t2 - t1);
	}
	
	
	// close GL context and any other GLFW resources
	glfwTerminate();
	system("pause");
	return 0;
}