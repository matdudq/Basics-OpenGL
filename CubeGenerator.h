#pragma once
#include <array>
#include "glm/glm.hpp"

struct CubeData
{
	static const unsigned int VERTEX_BUFFER_COUNT = 192;
	static const unsigned int INDICES_COUNT = 36;

	std::array<float, VERTEX_BUFFER_COUNT> vertexBuffer;
	std::array<unsigned int, INDICES_COUNT> indexBuffer;


};

CubeData GenerateCube(float size, glm::vec3 position)
{
	CubeData cubeToReturn;

	glm::vec3 wallsNormals[6] = { glm::vec3(0,0,-1),
								 glm::vec3(1,0,0),
								 glm::vec3(0,0,1),
								 glm::vec3(-1,0,0),
								 glm::vec3(0,1,0),
								 glm::vec3(0,-1,0) };

	cubeToReturn.vertexBuffer = {
			-size + position.x, -size + position.y, -size + position.z, 0, 0, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //0
			 size + position.x, -size + position.y, -size + position.z, 1, 0, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //1
			 size + position.x,  size + position.y, -size + position.z, 1, 1, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //2
			-size + position.x,  size + position.y, -size + position.z, 0, 1, wallsNormals[0].x, wallsNormals[0].y, wallsNormals[0].z, //3

			 size + position.x, -size + position.y, -size + position.z, 1, 0, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //1
			 size + position.x, -size + position.y,  size + position.z, 0, 0, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //5
			 size + position.x,  size + position.y,  size + position.z, 0, 1, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //6
			 size + position.x,  size + position.y, -size + position.z, 1, 1, wallsNormals[1].x, wallsNormals[1].y, wallsNormals[1].z, //2

			 size + position.x, -size + position.y,  size + position.z, 0, 0, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //5
			-size + position.x, -size + position.y,  size + position.z, 1, 0, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //4
			-size + position.x,  size + position.y,  size + position.z, 1, 1, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //7
			 size + position.x,  size + position.y,  size + position.z, 0, 1, wallsNormals[2].x, wallsNormals[2].y, wallsNormals[2].z, //6

			-size + position.x, -size + position.y,  size + position.z, 1, 0, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //4
			-size + position.x, -size + position.y, -size + position.z, 0, 0, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //0
			-size + position.x,  size + position.y, -size + position.z, 0, 1, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //3
			-size + position.x,  size + position.y,  size + position.z, 1, 1, wallsNormals[3].x, wallsNormals[3].y, wallsNormals[3].z, //7

			-size + position.x,  size + position.y, -size + position.z, 0, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //3
			 size + position.x,  size + position.y, -size + position.z, 1, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //2
			 size + position.x,  size + position.y,  size + position.z, 0, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //6
			-size + position.x,  size + position.y,  size + position.z, 1, 1, wallsNormals[4].x, wallsNormals[4].y, wallsNormals[4].z, //7

			-size + position.x, -size + position.y, -size + position.z, 0, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //0
			 size + position.x, -size + position.y, -size + position.z, 1, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //1
			 size + position.x, -size + position.y,  size + position.z, 0, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //5
			-size + position.x, -size + position.y,  size + position.z, 1, 0, wallsNormals[5].x, wallsNormals[5].y, wallsNormals[5].z, //4
	};

	cubeToReturn.indexBuffer = {
		0,1,3,
		1,2,3,
		4,5,7,
		5,6,7,
		8,9,11,
		9,10,11,
		12,13,15,
		13,14,15,
		16,17,19,
		17,18,19,
		20,21,23,
		21,22,23
	};

	return cubeToReturn;
}