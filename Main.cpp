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

/*data structure for the image used for  texture mapping */
typedef struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
} Image;

Image *TextureImage;

typedef struct RGB {
	GLubyte r;
	GLubyte g;
	GLubyte b;
} RGB;

RGB myimage[64][64];
RGB* g_pixel;

//forward declaration of image loading and texture set-up code
int ImageLoad(char *filename, Image *image);
GLvoid LoadTexture(char* image_file, int tex_id);

/* projection matrix */
void SetProjectionMatrix() {
	glm::mat4 Projection = glm::perspective(90.0f, (float)w_width / w_height, 0.1f, 300.0f);
	safe_glUniformMatrix4fv(h_uProjMatrix, glm::value_ptr(Projection));
}

/* view matrix */
void SetView() {
	glm::mat4 camera = glm::lookAt(eye, lookAt, up);
	safe_glUniformMatrix4fv(h_uViewMatrix, glm::value_ptr(camera));
}

/* Set the model transforms for sphere */
void SetSkyModel()
{
	glm::vec3 ax = glm::vec3(0, 1, 0);
	float initAngle = 20.0;

	glm::mat4 Trans = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(100.0, 100.0, 100.0));

	safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(Trans*Scale));
}

/*draw function for skybox*/
void drawSky() {

	SetSkyModel();
	

	//set up the texture unit
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	safe_glUniform1f(h_uSky, 1.0);

	safe_glUniform1i(h_uTexUnit, 0);

	safe_glEnableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj1);
	safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj1);
	safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj1);
	safe_glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj1);
	glDrawElements(GL_TRIANGLES, g_SkyiboLen, GL_UNSIGNED_SHORT, 0);

	/////////////////////////////////////////////////////////////
	//set up the texture unit
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 1);

	safe_glEnableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj2);
	safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj2);
	safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj2);
	safe_glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj2);
	glDrawElements(GL_TRIANGLES, g_SkyiboLen, GL_UNSIGNED_SHORT, 0);

	//////////////////////////////////////////////////////////////
	//set up the texture unit
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 2);


	safe_glEnableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj3);
	safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj3);
	safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj3);
	safe_glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj3);
	glDrawElements(GL_TRIANGLES, g_SkyiboLen, GL_UNSIGNED_SHORT, 0);

	//////////////////////////////////////////////////////////////
	//set up the texture unit
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 3);


	safe_glEnableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj4);
	safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj4);
	safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj4);
	safe_glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj4);
	glDrawElements(GL_TRIANGLES, g_SkyiboLen, GL_UNSIGNED_SHORT, 0);

	/////////////////////////////////////////////////////////////
	//set up the texture unit
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 4);

	safe_glEnableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj5);
	safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj5);
	safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	safe_glEnableVertexAttribArray(h_aTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj5);
	safe_glVertexAttribPointer(h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj5);
	glDrawElements(GL_TRIANGLES, g_SkyiboLen, GL_UNSIGNED_SHORT, 0);

	//////////////////////////////////////////////////////////////

	safe_glDisableVertexAttribArray(h_aPosition);
	safe_glDisableVertexAttribArray(h_aNormal);
	safe_glDisableVertexAttribArray(h_aTexCoord);

	safe_glUniform1f(h_uSky, 0.0);

	//Disable the shader
	glDisable(GL_TEXTURE_2D);
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

	safe_glUniform1f(h_uOutline, 1.0f);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	for (std::vector<GameObject>::iterator it = env.begin(); it != env.end(); ++it) {
		it->render();
	}

	for (int i = 0; i < MAX_PLAYERS; i++) {
		players[i].render();
	}

	safe_glUniform1f(h_uOutline, 0.0f);
	glCullFace(GL_BACK);
	
	for (std::vector<GameObject>::iterator it = env.begin(); it != env.end(); ++it) {
		it->render();
	}

	for (int i = 0; i < MAX_PLAYERS; i++) {
		players[i].render();
	}
	glDisable(GL_CULL_FACE);

	drawSky();
	
	

}
void initSky(){
	float SkyPos1[] = {
		-0.5, -0.5, -0.5, //back  
		-0.5, 0.5, -0.5,
		0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
	};

	float SkyNormal1[] = {
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
	};

	static GLfloat SkyTex1[] = {
		1.0, 0.0, 
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
	};

	unsigned short ndx1[] = { 0, 1, 2, 2, 3, 0 };

	g_SkyiboLen = 6;

	glGenBuffers(1, &SkyBuffObj1);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyPos1), SkyPos1, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyNormalBuffObj1);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyNormal1), SkyNormal1, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyIndxBuffObj1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ndx1), ndx1, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyTexBuffObj1);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyTex1), SkyTex1, GL_STATIC_DRAW);

	float SkyPos2[] = {
		0.5, -0.5, 0.5, //right
		0.5, 0.5, 0.5,
		0.5, 0.5, -0.5,
		0.5, -0.5, -0.5,
	};

	float SkyNormal2[] = {
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
	};

	static GLfloat SkyTex2[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
	};

	unsigned short ndx2[] = { 0, 1, 2, 2, 3, 0 };

	glGenBuffers(1, &SkyBuffObj2);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyPos2), SkyPos2, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyNormalBuffObj2);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyNormal2), SkyNormal2, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyIndxBuffObj2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ndx2), ndx2, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyTexBuffObj2);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyTex2), SkyTex2, GL_STATIC_DRAW);

	float SkyPos3[] = {
		-0.5, -0.5, 0.5, //front
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5,
		0.5, -0.5, 0.5,
	};

	float SkyNormal3[] = {
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
	};

	static GLfloat SkyTex3[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
	};

	unsigned short ndx3[] = { 0, 1, 2, 2, 3, 0 };

	glGenBuffers(1, &SkyBuffObj3);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyPos3), SkyPos3, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyNormalBuffObj3);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyNormal3), SkyNormal3, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyIndxBuffObj3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ndx3), ndx3, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyTexBuffObj3);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyTex3), SkyTex3, GL_STATIC_DRAW);

	float SkyPos4[] = {
		-0.5, -0.5, -0.5, //left
		-0.5, 0.5, -0.5,
		-0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,
	};

	float SkyNormal4[] = {
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
	};

	static GLfloat SkyTex4[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
	};

	unsigned short ndx4[] = { 0, 1, 2, 2, 3, 0 };

	glGenBuffers(1, &SkyBuffObj4);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyPos4), SkyPos4, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyNormalBuffObj4);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyNormal4), SkyNormal4, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyIndxBuffObj4);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ndx4), ndx4, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyTexBuffObj4);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyTex4), SkyTex4, GL_STATIC_DRAW);

	float SkyPos5[] = {
		-0.5, 0.5, -0.5,  //top
		0.5, 0.5, -0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5,
	};

	float SkyNormal5[] = {
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
	};

	static GLfloat SkyTex5[] = {
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
		0.0, 0.0,
	};

	unsigned short ndx5[] = { 0, 1, 2, 2, 3, 0 };

	glGenBuffers(1, &SkyBuffObj5);
	glBindBuffer(GL_ARRAY_BUFFER, SkyBuffObj5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyPos5), SkyPos5, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyNormalBuffObj5);
	glBindBuffer(GL_ARRAY_BUFFER, SkyNormalBuffObj5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyNormal5), SkyNormal5, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyIndxBuffObj5);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, SkyIndxBuffObj5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ndx5), ndx5, GL_STATIC_DRAW);

	glGenBuffers(1, &SkyTexBuffObj5);
	glBindBuffer(GL_ARRAY_BUFFER, SkyTexBuffObj5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SkyTex5), SkyTex5, GL_STATIC_DRAW);


}
void Initialize()	// Any GL Init Code 
{
	initSky();
	// Start Of User Initialization
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Black Background
	glClearDepth(1.0f);	// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing
	glEnable(GL_DEPTH_TEST);// Enable Depth Testing

	/* texture specific settings */
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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
	h_uSky = safe_glGetUniformLocation(ShadeProg, "sky");
	h_aTexCoord = safe_glGetAttribLocation(ShadeProg, "aTexCoord");
	h_uTexUnit = safe_glGetUniformLocation(ShadeProg, "uTexUnit");

	printf("sucessfully installed shader %d\n", ShadeProg);
	return 1;
}

void SetupScene() {
	/* environment */
	
	GameObject ground = GameObject();
	ground.setupVertices("untitled.dae");
	ground.scale = glm::vec3(35.0f, 1.0f, 2.0f);
	ground.color = glm::vec3(0.0f, 0.5f, 0.5f);
	env.push_back(ground);
	GameObject platform = GameObject();
	platform.scale = glm::vec3(4.0f, 0.15f, 2.0f);
	platform.position = glm::vec3(3.0f, 6.5f, 0.0f);
	platform.setupVertices("untitled.dae");
	platform.color = glm::vec3(0.f, 0.5f, 0.5f);
	env.push_back(platform);

	/* characters */
	GameObject p1 = GameObject();
	//p1.scale = glm::vec3(0.5f, 2.0f, 0.5f);
	p1.scale = glm::vec3(.3f, .3f, .3f);
	p1.position = glm::vec3(-5.0f, 4.5f, 0.0f);
	p1.rotation = 0;
	p1.color = glm::vec3(0.0f, 1.0f, 0.0f);
	p1.setupVertices("spiderman3.dae");
	players[0] = p1;

	GameObject p2 = GameObject();
	p2.scale = glm::vec3(0.5f, 0.5f, 0.5f);
	p2.position = glm::vec3(5.0f, 4.5f, 0.0f);
	p2.rotation = -90;
	p2.color = glm::vec3(1.0f, 0.0f, 0.0f);
	p2.setupVertices("astro.dae");
	players[1] = p2;

	
}

void ProcessMovement() {
	/* player 1 */
	if (W_key && !S_key) {					//up
		if (players[0].velocity.y == 0.0f) {
			players[0].velocity.y = 2.5f;
			//players[0].position.y += 0.015;
			players[0].falling = true;
		}
	}
	else if (!W_key && S_key) {				//down
		//players[0].position.y -= 0.015;
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

	/*calls to load the bmps*/
	LoadTexture((char *)"delirious_back.bmp", 0);
	LoadTexture((char *)"delirious_right.bmp", 1);
	LoadTexture((char *)"delirious_front.bmp", 2);
	LoadTexture((char *)"delirious_left.bmp", 3);
	LoadTexture((char *)"delirious_top.bmp", 4);

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

//routines to load in a bmp files - must be 2^nx2^m and a 24bit bmp
GLvoid LoadTexture(char* image_file, int texID) {

	TextureImage = (Image *)malloc(sizeof(Image));
	if (TextureImage == NULL) {
		printf("Error allocating space for image");
		exit(1);
	}
	std::cout << "trying to load " << image_file << std::endl;
	if (!ImageLoad(image_file, TextureImage)) {
		exit(1);
	}
	/*  2d texture, level of detail 0 (normal), 3 components (red, green, blue),            */
	/*  x size from image, y size from image,                                              */
	/*  border 0 (normal), rgb color data, unsigned byte data, data  */
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		TextureImage->sizeX, TextureImage->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /*  cheap scaling when image bigger than texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /*  cheap scaling when image smalled than texture*/

}


/* BMP file loader loads a 24-bit bmp file only */

/*
* getint and getshort are help functions to load the bitmap byte by byte
*/
static unsigned int getint(FILE *fp) {
	int c, c1, c2, c3;

	/*  get 4 bytes */
	c = getc(fp);
	c1 = getc(fp);
	c2 = getc(fp);
	c3 = getc(fp);

	return ((unsigned int)c) +
		(((unsigned int)c1) << 8) +
		(((unsigned int)c2) << 16) +
		(((unsigned int)c3) << 24);
}

static unsigned int getshort(FILE *fp){
	int c, c1;

	/* get 2 bytes*/
	c = getc(fp);
	c1 = getc(fp);

	return ((unsigned int)c) + (((unsigned int)c1) << 8);
}

/*  quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  */

int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size;                 /*  size of the image in bytes. */
	unsigned long i;                    /*  standard counter. */
	unsigned short int planes;          /*  number of planes in image (must be 1)  */
	unsigned short int bpp;             /*  number of bits per pixel (must be 24) */
	char temp;                          /*  used to convert bgr to rgb color. */

	/*  make sure the file is there. */
	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	/*  seek through the bmp header, up to the width height: */
	fseek(file, 18, SEEK_CUR);

	/*  No 100% errorchecking anymore!!! */

	/*  read the width */    image->sizeX = getint(file);

	/*  read the height */
	image->sizeY = getint(file);

	/*  calculate the size (assuming 24 bits or 3 bytes per pixel). */
	size = image->sizeX * image->sizeY * 3;

	/*  read the planes */
	planes = getshort(file);
	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	/*  read the bpp */
	bpp = getshort(file);
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	/*  seek past the rest of the bitmap header. */
	fseek(file, 24, SEEK_CUR);

	/*  read the data.  */
	image->data = (char *)malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i = 0; i<size; i += 3) { /*  reverse all of the colors. (bgr -> rgb) */
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}

	fclose(file); /* Close the file and release the filedes */

	/*  we're done. */
	return 1;
}
