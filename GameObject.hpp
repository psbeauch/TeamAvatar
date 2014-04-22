#include "Globals.hpp"
#define NO_COL 0
#define LEFT_COL 2
#define RIGHT_COL 3
#define LOWER_COL 4
#define UPPER_COL 5

class GameObject {
public:
	glm::vec3 position, velocity, scale, color;
	float rotation;
	GLuint vaoID;
	GLuint vboID[1];
	GLuint VBO, IBO, NBO;	//vertex, index, normal
	int IBOLen;
	int ShadeProg;
	bool falling;

	GameObject();
	void setupVertices(float *vertices, int numVerts, unsigned short *indexes, int numIndexes, float *normals);
	virtual void render();
	int checkCollision(GameObject go);
	//bool setupVertices(const std::string& file);
};
