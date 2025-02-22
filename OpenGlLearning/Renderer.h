#pragma once

#include<GLEW/glew.h>

#include "VertexArray.h"

#include "IndexBuffer.h"

#include "Shader.h"

class Renderer
{
public:
	void Clear();
	void SetClearColor() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};