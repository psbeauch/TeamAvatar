#include "Globals.hpp"
#define NO_COL 0
#define LEFT_COL 2
#define RIGHT_COL 3
#define LOWER_COL 4
#define UPPER_COL 5
#include <string>
#ifndef ASSIMP_H
#define ASSIMP_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif
#include <vector>

class GameObject {
public:
	glm::vec3 position, velocity, scale, color;
	float rotation;
	GLuint vaoID;
	GLuint vboID[1];
	std::vector<GLuint> VBO;	//vertex
	std::vector<GLuint> IBO;	//index
	std::vector<GLuint> NBO;	//normal
	std::vector<int> IBOLen;
	int ShadeProg;
	bool falling;
	Assimp::Importer importer;
	std::vector<float*> verts;
	std::vector<float> vertices;
	std::vector<unsigned short> indices;
	std::vector<float> normals;

	GameObject();
	void setupVertices(float *vertices, int numVerts, unsigned short *indexes, int numIndexes, float *normals);
	virtual void render();
	int checkCollision(GameObject go);
	bool setupVertices(const std::string& file);
	bool process_mesh(aiMesh* mesh, const aiScene *scene);
	bool recurse_through_nodes(aiNode *node, const aiScene *scene);
};
