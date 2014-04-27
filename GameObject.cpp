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
	IBOLen.resize(1);
	VBO.resize(1);
	IBO.resize(1);
	NBO.resize(1);

	IBOLen[0] = numIndexes;
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &IBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * numIndexes, indexes, GL_STATIC_DRAW);

	glGenBuffers(1, &NBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, NBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned short) * numVerts, normals, GL_STATIC_DRAW);
	
}

bool GameObject::process_mesh(aiMesh* mesh, const aiScene *scene) {
	
	int v_start = vertices.size();
	int i_start = indices.size();
	fprintf(stderr, "\tv_start = %d\ti_start = %d\n", v_start, i_start);
	fprintf(stderr, "\t\tImporting %d vertices and normals\n", mesh->mNumVertices);
	for (int j = 0; j < mesh->mNumVertices; j++) {
		const aiVector3D *v, *n;
		if (mesh->HasPositions()) {
			v = &(mesh->mVertices[j]);
			vertices.push_back(v->x);
			vertices.push_back(v->y);
			vertices.push_back(v->z);
		}
		else {
			fprintf(stderr, "---No vertices detected in mesh---\n");
			return false;
		}
		if (mesh->HasNormals()) {
			n = &(mesh->mNormals[j]);
			normals.push_back(n->x);
			normals.push_back(n->y);
			normals.push_back(n->z);
		}
		else {
			fprintf(stderr, "---No normals detected in mesh---\n");
			return false;
		}
	}
	fprintf(stderr, "\t\tImporting %d faces\n", mesh->mNumFaces);
	for (int j = 0; j < mesh->mNumFaces; j++) {
		aiFace *f = &(mesh->mFaces[j]);
		for (int k = 0; k < f->mNumIndices; k++) {
			if (f->mNumIndices != 3) {
				fprintf(stderr, "---Error triangulating mesh---\n");
				return false;
			}
			indices.push_back((unsigned short)f->mIndices[k]);
		}
	}

	IBOLen.push_back(mesh->mNumFaces * 3);
	fprintf(stderr, "IBOLen[%d] = %d\n", IBOLen.size() - 1, IBOLen[IBOLen.size() - 1]);
	VBO.push_back(0);
	glGenBuffers(1, &VBO[VBO.size() - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VBO.size() - 1]);
	fprintf(stderr, "VBO[%d] = %d\n", VBO.size() - 1, VBO[VBO.size() - 1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* mesh->mNumVertices * 3, &vertices[v_start], GL_STATIC_DRAW);

	IBO.push_back(0);
	glGenBuffers(1, &IBO[IBO.size() - 1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[IBO.size() - 1]);
	fprintf(stderr, "IBO[%d] = %d\n", IBO.size() - 1, IBO[IBO.size() - 1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)* mesh->mNumFaces * 3, &indices[i_start], GL_STATIC_DRAW);

	if (mesh->HasNormals()) {
		NBO.push_back(0);
		glGenBuffers(1, &NBO[NBO.size() - 1]);
		glBindBuffer(GL_ARRAY_BUFFER, NBO[NBO.size() - 1]);
		fprintf(stderr, "NBO[%d] = %d\n", NBO.size() - 1, NBO[NBO.size() - 1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* mesh->mNumVertices * 3, &normals[v_start], GL_STATIC_DRAW);
	}
	return true;
}

bool GameObject::recurse_through_nodes(aiNode *node, const aiScene *scene) {
	printf("Node name: %s\n", node->mName.C_Str());
	printf("# of children: %d\n", node->mNumChildren);
	printf("# of meshes: %d\n", node->mNumMeshes);
	bool success = true;

	for (int i = 0; i < node->mNumMeshes; i++) {
		fprintf(stderr, "Processing mesh %d\n", i);
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		if (!process_mesh(mesh, scene)) success = false;
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		if (!recurse_through_nodes(node->mChildren[i], scene)) success = false;
	}
	return success;
}

bool GameObject::setupVertices(const std::string& file) {
	const aiScene* scene = importer.ReadFile(file.c_str(),
	aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
	aiProcess_GenNormals | aiProcess_ValidateDataStructure |
	aiProcess_ImproveCacheLocality | aiProcess_RemoveRedundantMaterials |
	aiProcess_FixInfacingNormals | aiProcess_FindInvalidData |
	aiProcess_OptimizeMeshes);

	if (scene == NULL) {
		fprintf(stderr, "Error importing file: %s\n", file.c_str());
		fprintf(stderr, "%s\n", importer.GetErrorString());
		return false;
	}
	else {
		fprintf(stderr, "Successful import of %s\n", file.c_str());
	}

	const aiNode *node = scene->mRootNode;

	if (recurse_through_nodes(scene->mRootNode, scene)) {
		fprintf(stderr, "Successful processing of %s\n", file.c_str());
	}
	else {
		fprintf(stderr, "Error processing of %s\n", file.c_str());
		return false;
	}
	return true;
}

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
	//safe_glUniform1f(h_uOutline, 0.0f);

	for (int i = 0; i < IBOLen.size(); i++) {
		/* setting vertices */
		safe_glEnableVertexAttribArray(h_aPosition);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

		/* setting normals */
		safe_glEnableVertexAttribArray(h_aNormal);
		glBindBuffer(GL_ARRAY_BUFFER, NBO[i]);
		safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO[i]);

		/* draw */
		//glDrawElements(GL_TRIANGLES, IBOLen, GL_UNSIGNED_SHORT, 0);
		glDrawElements(GL_TRIANGLES, IBOLen[i], GL_UNSIGNED_SHORT, 0);

		/* clean up */
		safe_glDisableVertexAttribArray(h_aPosition);
		safe_glDisableVertexAttribArray(h_aNormal);
	}
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