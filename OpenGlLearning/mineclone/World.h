#pragma once

#include "Perlin.h"
#include "Light.h"
#include "Chunk.h"

class World
{
	std::vector<Chunk> chunks;

	Light light = Light(Vector3{ 0.5f, -0.5f, 0.0f });

	PerlinNoise noise;

public:

	void AddChunk(Vector3 chunk_pos);

	inline Vector3 GetLightDir() { return light.GetDir(); }

	inline std::vector<Chunk>& GetChunks() { return chunks; }
};