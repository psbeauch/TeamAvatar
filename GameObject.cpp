#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "GameObject.hpp"
#endif
#include "GLSL_helper.h"

GameObject::GameObject() {
	position = glm::vec3(0.0f);
	velocity = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	color = glm::vec3(0.7f);
	rotation = 0.0f;
	falling = true;
}

void GameObject::setupVertices(float *vertices, int numVerts, unsigned short *indexes, int numIndexes, float *normals) {
	/*
	glGenVertexArrays(ShadeProg, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(ShadeProg, vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	*/

	IBOLen = numIndexes;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numIndexes, indexes, GL_STATIC_DRAW);

	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned short) * numVerts, normals, GL_STATIC_DRAW);
}

//bool GameObject::setupVertices(const std::string& file) {
	/*Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(file,
		aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
		aiProcess_GenNormals | aiProcess_ValidateDataStructure |
		aiProcess_ImproveCacheLocality | aiProcess_RemoveRedundantMaterials |
		aiProcess_FixInfacingNormals | aiProcess_FindInvalidData |
		aiProcess_OptimizeMeshes);

	if (scene == NULL) {
		fprintf(stderr, "ERROR IMPORTING FILE: %s\n", file);
		fprintf(stderr, "%s\n", importer.GetErrorString());
		return false;
	}
	*/
	//return true;
//}

void GameObject::render() {
	/* model transforms */
	glm::mat4 t, s, r;
	t = glm::translate(glm::mat4(1.0f), position);
	s = glm::scale(glm::mat4(1.0f), scale);
	r = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 TSR = t * s * r;
	safe_glUniformMatrix4fv(h_uModelMatrix, glm::value_ptr(TSR));

	/* color */
	safe_glUniform3f(h_uCol, color.x, color.y, color.z);

	/* outline for cel shading*/
	safe_glUniform1f(h_uOutline, 0.0f);

	/* setting vertices */
	safe_glEnableVertexAttribArray(h_aPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/* setting normals */
	safe_glEnableVertexAttribArray(h_aNormal);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	/* draw */
	glDrawElements(GL_TRIANGLES, IBOLen, GL_UNSIGNED_SHORT, 0);

	/* clean up */
	safe_glDisableVertexAttribArray(h_aPosition);
	safe_glDisableVertexAttribArray(h_aNormal);
}

int GameObject::checkCollision(GameObject go) {
	/* horizontal checks */
	float left_bound = position.x - (scale.x);
	float right_bound = position.x + (scale.x);
	float go_left_bound = go.position.x - (go.scale.x);
	float go_right_bound = go.position.x + (go.scale.x);
	float upper_bound = position.y + (scale.y);
	float lower_bound = position.y - (scale.y);
	float go_upper_bound = go.position.y + (go.scale.y);
	float go_lower_bound = go.position.y - (go.scale.y);

	/*
	if ((left_bound < go_right_bound && left_bound > go_left_bound) || (right_bound < go_right_bound && right_bound > go_left_bound)) {
		if ((upper_bound < go_upper_bound && upper_bound > go_lower_bound) || (lower_bound < go_upper_bound && lower_bound > go_lower_bound)) {
			return UPPER_COL;
		}
		if ((go_upper_bound < upper_bound && go_upper_bound > lower_bound) || (go_lower_bound < upper_bound && go_lower_bound > lower_bound)) {
			return UPPER_COL;
		}
	}
	if ((go_left_bound < right_bound && go_left_bound > left_bound) || (go_right_bound < right_bound && go_right_bound > left_bound)) {
		if ((upper_bound < go_upper_bound && upper_bound > go_lower_bound) || (lower_bound < go_upper_bound && lower_bound > go_lower_bound)) {
			return true;
		}
		if ((go_upper_bound < upper_bound && go_upper_bound > lower_bound) || (go_lower_bound < upper_bound && go_lower_bound > lower_bound)) {
			return true;
		}
	}
	*/

	if ((lower_bound < go_upper_bound && lower_bound > go_lower_bound)) {
		if (left_bound < go_right_bound && left_bound > go_left_bound) {
			return LOWER_COL;
		}
	}
	return NO_COL;
}