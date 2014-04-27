#ifndef GLOBAL_H
#define GLOBAL_H
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* handles */
extern GLint h_aPosition;
extern GLint h_aNormal;
extern GLint h_uModelMatrix;
extern GLint h_uViewMatrix;
extern GLint h_uProjMatrix;
extern GLint h_uLPos;
extern GLint h_uLColor;
extern GLint h_uCol;
extern GLint h_uCameraPos;
extern GLint h_uOutline;

/*skybox handles*/
extern GLuint SkyBuffObj1, SkyIndxBuffObj1, SkyNormalBuffObj1, SkyTexBuffObj1;
extern GLuint SkyBuffObj2, SkyIndxBuffObj2, SkyNormalBuffObj2, SkyTexBuffObj2;
extern GLuint SkyBuffObj3, SkyIndxBuffObj3, SkyNormalBuffObj3, SkyTexBuffObj3;
extern GLuint SkyBuffObj4, SkyIndxBuffObj4, SkyNormalBuffObj4, SkyTexBuffObj4;
extern GLuint SkyBuffObj5, SkyIndxBuffObj5, SkyNormalBuffObj5, SkyTexBuffObj5;
extern int g_SkyiboLen;
/*texturen handles*/
extern GLint h_uTexUnit;
extern GLint h_aTexCoord;
extern GLint h_uSky;

extern int w_width, w_height;
extern bool debug;
extern int shade;
extern int ShadeProg;

/* camera */
extern glm::vec3 eye;
extern glm::vec3 up;
extern glm::vec3 lookAt;
extern float MIN_DIST;
extern float MAX_DIST;
extern float MIN_CAM_X;
extern float MAX_CAM_X;
extern float DEF_CAM_X;
extern float DEF_CAM_Y;
extern float DEF_CAM_Z;

/* lighting */
extern glm::vec3 lightPos;

extern glm::vec3 playerSpawn;

#endif