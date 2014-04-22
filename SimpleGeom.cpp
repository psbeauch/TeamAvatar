#ifndef GLOBAL_H
#include "Globals.hpp"
#endif

#include "SimpleGeom.hpp"

GameObject CubeObject() {
	float CubePos[] = {
		-1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		-1.0, 1.0, -1.0,
		-1.0, 1.0, 1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, -1.0,
		1.0, 1.0, 1.0
	};

	unsigned short idx[] = { 0, 1, 2,
		1, 2, 3,
		0, 2, 4,
		2, 4, 6,
		2, 3, 7,
		2, 6, 7,
		1, 3, 7,
		1, 5, 7,
		4, 5, 6,
		5, 6, 7,
		0, 1, 5,
		0, 4, 5

	};

	float CubeNormal[] = { -1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0
	};

	GameObject go = GameObject();
	go.color = glm::vec3(0.2f, 0.2f, 0.8f);
	go.setupVertices(CubePos, 24, idx, 36, CubeNormal);
	return go;
}

GameObject PlaneObject() {
	float g_groundSize = 5;
	float g_groundY = 0;
	// A x-z plane at y = g_groundY of dimension [-g_groundSize, g_groundSize]^2
	float GrndPos[] = {
		-g_groundSize, g_groundY, -g_groundSize,
		-g_groundSize, g_groundY, g_groundSize,
		g_groundSize, g_groundY, g_groundSize,
		g_groundSize, g_groundY, -g_groundSize
	};

	float GrndNorm[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};

	unsigned short idx[] = { 0, 1, 2, 0, 2, 3 };

	GameObject go = GameObject();
	go.color = glm::vec3(0.2f, 0.8f, 0.3f);
	go.setupVertices(GrndPos, 12, idx, 6, GrndNorm);
	return go;
}