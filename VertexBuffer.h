#pragma once
#include "glad/glad.h"
#include "Utilities.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID;
};
