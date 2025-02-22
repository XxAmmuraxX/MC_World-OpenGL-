#include "World.h"

void World::AddChunk(Vector3 chunk_pos)
{
	chunks.push_back(Chunk(chunk_pos,noise));
}
