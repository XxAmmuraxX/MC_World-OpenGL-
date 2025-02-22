#pragma once
#include <time.h>
#include "Block.h"
#include <vector>

class Chunk
{ 

public:

	const static int HEIGHT = 70, WIDTH = 16;
private:

	Vector3 pos;
	
public:

	Block blocks[WIDTH][HEIGHT][WIDTH];

	void GenerateChunk(PerlinNoise& noise)
	{
		for(int y = 0; y < HEIGHT; y++)
			for(int x = 0; x < WIDTH; x++)
				for (int z = 0; z < WIDTH; z++)
				{
					unsigned int block_id = 0;

					

					float minHeight = Chunk::HEIGHT / 4;
					float maxHeight = Chunk::HEIGHT;

					float scale1 = 0.005f;

					float scale2 = 0.015f;

					Vector3 world_block_pos = Vector3Add({ pos.x * WIDTH, pos.y * HEIGHT, pos.z * WIDTH },
						Vector3{ (float)x,(float)y,(float)z });

					float perlin1 = noise.noise(scale1*world_block_pos.x,0.0f,scale1*world_block_pos.z);
					float perlin2 = noise.noise(scale2*world_block_pos.x,0.0f,scale2*world_block_pos.z);

					float perlin_sum =  sin((perlin1 + perlin2) / 2);

					float ground_height = minHeight + perlin_sum * (maxHeight - minHeight);

					if (y <= Chunk::HEIGHT / 2 && y >= ground_height)
						block_id = blue_wool;

					if (y < ground_height)
						block_id = grass;
					
					if (y < ground_height - 1)
						block_id = dirt;

					if(y < ground_height - 5)
						block_id = stone;

					if (y < ground_height - 10)
					{
						if (std::rand() % (int)ground_height <= 1)
						{
							block_id = coal_ore;
						}
					}
					
					if (y < ground_height - 16)
					{
						if (std::rand() % (int)ground_height * 5 <= 1)
						{
							block_id = iron_ore;
						}
					}
					
					if (y < ground_height - 30)
					{
						if (std::rand() % (int)ground_height * 10 <= 1)
						{
							block_id = gold_ore;
						}
					}
				
					if (y == 0)
						block_id = bedrock;

					if (y == 1)
						if (std::rand() % 100 < 50)
							block_id = bedrock;

					if (y == 2)
						if (std::rand() % 100 < 20)
							block_id = bedrock;

					if (y < Chunk::HEIGHT)
					{

						if (x + 1 < Chunk::WIDTH && x - 1 >= 0 && z + 1 < Chunk::WIDTH && z - 1 >= 0)
						{
							if(blocks[x][y - 1][z].GetId() == grass && block_id != blue_wool)
								if(std::rand() % 100 < 5)
									block_id = wood;

							if (blocks[x][y - 1][z].GetId() == wood && y < ground_height + 4)
								block_id = wood;
							
							if (y == (int)ground_height + 4 && blocks[x][y - 1][z].GetId() == wood)
							{
								block_id = leaves;
								for(int i = -1 ; i < 2 ; i++)
									for(int j = -1; j < 2 ; j++)
										if(i != j || j != 0)
											blocks[x + i][y - 1][z + j].SetId(leaves);
							}

						}
					}

					blocks[x][y][z] = Block(world_block_pos, block_id);

				}

	}
	
	Chunk(Vector3 pos, PerlinNoise& noise) : pos(pos) { GenerateChunk(noise); std::srand(time(0)); }

	void SetPos(Vector3 pos) { this->pos = pos; }

};