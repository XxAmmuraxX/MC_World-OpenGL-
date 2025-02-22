#pragma once

#include "raymath.h"

//Vector2 top_left;
//Vector2 bot_left;
//Vector2 top_right;
//Vector2 bot_right;


enum BlockType
{
	air = 0,
	stone = 1,
	dirt = 2,
	grass = 3,
	water = 14,
	bedrock = 17,
	wood = 20,
	leaves = 22,
	gold_ore = 32,
	iron_ore = 33,
	coal_ore = 34,
	blue_wool = 71

};

class Block
{
	Vector3 local_pos;

	unsigned int id;

public:

	Block() :local_pos(Vector3Zero()), id(0) {}

	Block(Vector3 pos, unsigned int id) : local_pos(pos), id(id) {}

	inline Vector3 GetPos() { return local_pos; }

	inline unsigned int GetId() { return id; }

	void SetId(unsigned int id) { this->id = id; }
};

class BlockTextures
{
	int atlas_x, atlas_y;

public:

	BlockTextures(int atlas_x, int atlas_y) : atlas_x(atlas_x), atlas_y(atlas_y) {}

	Vector2 GetTopLeft(unsigned int id, unsigned int face);
    Vector2 GetBotLeft(unsigned int id, unsigned int face);
	Vector2 GetTopRight(unsigned int id, unsigned int face);
	Vector2 GetBotRight(unsigned int id, unsigned int face);
};

