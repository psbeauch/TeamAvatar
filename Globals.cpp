#include "Globals.hpp"

GLint h_aPosition;
GLint h_aNormal;
GLint h_uModelMatrix;
GLint h_uViewMatrix;
GLint h_uProjMatrix;
GLint h_uLPos;
GLint h_uLColor;
GLint h_uCol;
GLint h_uCameraPos;
GLint h_uOutline;

int w_width = 1280, w_height = 720;
bool debug = false;
int shade = 1;
int ShadeProg;

glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, -5.0f);

float MIN_DIST = 10.0f;
float MAX_DIST = 30.0f;
float MIN_CAM_X = -20.0f;
float MAX_CAM_X = 20.0f;

float DEF_CAM_X = 0.0f;
float DEF_CAM_Y = 6.0f;
float DEF_CAM_Z = 10.0f;

glm::vec3 eye = glm::vec3(DEF_CAM_X, DEF_CAM_Y, DEF_CAM_Z);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lookAt = glm::vec3(DEF_CAM_X, DEF_CAM_X, 0.0f);

glm::vec3 playerSpawn = glm::vec3(0.0f, 3.5f, 0.0f);