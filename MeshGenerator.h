#pragma once
#include <array>
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

struct ShapeData
{
	std::vector<float>& const m_VertexBuffer;
	std::vector<unsigned int>& const m_IndexBuffer;

	ShapeData(std::vector<float>& const vertexBuffer, std::vector<unsigned int>& const indexBuffer) : m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer)
	{
	}
};

ShapeData& GenerateCube(float size, glm::vec3 position)
{
	glm::vec3 wallsNormals[6] = { glm::vec3(0,0,-1),
								 glm::vec3(1,0,0),
								 glm::vec3(0,0,1),
								 glm::vec3(-1,0,0),
								 glm::vec3(0,1,0),
								 glm::vec3(0,-1,0) };

	float m_VertexBuffer[] = {
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

	unsigned int m_IndexBuffer[] = {
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

	std::vector<float>* vertexBuffer = new std::vector<float>(&m_VertexBuffer[0],&m_VertexBuffer[191]);
	std::vector<unsigned int>* indexBuffer = new std::vector<unsigned int>(&m_IndexBuffer[0],&m_IndexBuffer[35]);

	return *(new ShapeData(*vertexBuffer, *indexBuffer));
}

ShapeData& GenerateEgg(float maximalRadius, float height, unsigned int resolution = 100)
{
	resolution = glm::clamp(resolution, 5U, UINT32_MAX);

	float verticalStep = height / (resolution - 1);
	float horizontalAngleStep = 2 * glm::pi<float>() / (resolution - 1);

	float actualOriginOffsetY = -height / 2;
	glm::vec3 actualOriginOffset = glm::vec3(0, 0, 0);

	std::vector<glm::vec3> eggVertexPositionsArrayBuffer = std::vector<glm::vec3>();
	std::vector<glm::vec3> eggVertexNormalsArray = std::vector<glm::vec3>();
	std::vector<glm::vec2> eggVertexUVArrayBuffer = std::vector<glm::vec2>();
	std::vector<unsigned int>* indicesArray = new std::vector<unsigned int>();

	for (int i = 0; i < resolution; i++)
	{
		actualOriginOffset = glm::vec3(maximalRadius * glm::sqrt(glm::abs(glm::sin(((float)i) / (resolution - 1) * glm::pi<float>()))), 0, 0);
		for (int j = 0; j < resolution; j++)
		{
			actualOriginOffset = glm::rotateY(actualOriginOffset, horizontalAngleStep);
			eggVertexPositionsArrayBuffer.push_back(glm::vec3(actualOriginOffset.x, actualOriginOffsetY, actualOriginOffset.z));
			eggVertexUVArrayBuffer.push_back(glm::vec2(((float)j) / (resolution - 1), ((float)i) / (resolution - 1)));
		}
		actualOriginOffsetY += verticalStep;
	}

	std::vector<glm::vec3> eggVertexPositionsArray = std::vector<glm::vec3>();
	std::vector<glm::vec2> eggVertexUVArray = std::vector<glm::vec2>();

	for (int i = 0; i < resolution - 1; i++)
	{
		for (int j = 0; j < resolution - 1; j++)
		{

			unsigned int index0 = resolution * i + j;
			unsigned int index1 = resolution * i + j + 1;
			unsigned int index2 = resolution * (i + 1) + j;
			unsigned int index3 = resolution * (i + 1) + j + 1;

			eggVertexPositionsArray.push_back(eggVertexPositionsArrayBuffer[index0]);
			eggVertexPositionsArray.push_back(eggVertexPositionsArrayBuffer[index1]);
			eggVertexPositionsArray.push_back(eggVertexPositionsArrayBuffer[index2]);

			eggVertexPositionsArray.push_back(eggVertexPositionsArrayBuffer[index2]);
			eggVertexPositionsArray.push_back(eggVertexPositionsArrayBuffer[index3]);
			eggVertexPositionsArray.push_back(eggVertexPositionsArrayBuffer[index1]);

			eggVertexUVArray.push_back(eggVertexUVArrayBuffer[index0]);
			eggVertexUVArray.push_back(eggVertexUVArrayBuffer[index1]);
			eggVertexUVArray.push_back(eggVertexUVArrayBuffer[index2]);

			eggVertexUVArray.push_back(eggVertexUVArrayBuffer[index2]);
			eggVertexUVArray.push_back(eggVertexUVArrayBuffer[index3]);
			eggVertexUVArray.push_back(eggVertexUVArrayBuffer[index1]);

			glm::vec3 vec1 = eggVertexPositionsArrayBuffer[index2] - eggVertexPositionsArrayBuffer[index0];
			glm::vec3 vec2 = eggVertexPositionsArrayBuffer[index1] - eggVertexPositionsArrayBuffer[index0];
			glm::vec3 normal = glm::normalize(-glm::cross(vec1, vec2));

			eggVertexNormalsArray.push_back(normal);
			eggVertexNormalsArray.push_back(normal);
			eggVertexNormalsArray.push_back(normal);

			vec1 = eggVertexPositionsArrayBuffer[index1] - eggVertexPositionsArrayBuffer[index3];
			vec2 = eggVertexPositionsArrayBuffer[index2] - eggVertexPositionsArrayBuffer[index3];
			normal = glm::normalize(-glm::cross(vec1, vec2));

			eggVertexNormalsArray.push_back(normal);
			eggVertexNormalsArray.push_back(normal);
			eggVertexNormalsArray.push_back(normal);

			int indicesSize = indicesArray->size();

			indicesArray->push_back(indicesSize + 0);
			indicesArray->push_back(indicesSize + 1);
			indicesArray->push_back(indicesSize + 2);

			indicesArray->push_back(indicesSize + 3);
			indicesArray->push_back(indicesSize + 4);
			indicesArray->push_back(indicesSize + 5);
		}
	}

	std::vector<float>* vertexBuffer = new std::vector<float>();
	unsigned int eggVertexBufferSize = eggVertexPositionsArray.size();
	for (int i = 0; i < eggVertexBufferSize; i++)
	{
		vertexBuffer->push_back(eggVertexPositionsArray[i].x);
		vertexBuffer->push_back(eggVertexPositionsArray[i].y);
		vertexBuffer->push_back(eggVertexPositionsArray[i].z);

		vertexBuffer->push_back(eggVertexUVArray[i].x);
		vertexBuffer->push_back(eggVertexUVArray[i].y);

		vertexBuffer->push_back(eggVertexNormalsArray[i].x);
		vertexBuffer->push_back(eggVertexNormalsArray[i].y);
		vertexBuffer->push_back(eggVertexNormalsArray[i].z);
	}

	return *(new ShapeData(*vertexBuffer, *indicesArray));
}