#include "Block.h"

Vector2 BlockTextures::GetTopLeft(unsigned int id, unsigned int face)
{
    Vector2 pos = Vector2Zero();

    //if (id == stone || id == dirt || id == water)
    {
        pos.x = (id % 16) / 16.0f;
        pos.y = 1 - (id / 16) / 16.0f;
    }

    if (id == grass)
    {
        if (face == 20 || face == 100 || face == 120)
        {
            pos.x = 3 / 16.0f;
            pos.y = 1;
        }

        if (face == 40)
        {
            pos.x = 4 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }

        if (face == 60)
        {
            pos.x = 0 / 16.0f;
            pos.y = 1;
        }

        if (face == 80)
        {
            pos.x = 2 / 16.0f;
            pos.y = 1;
        }

    }

    return pos;
}

Vector2 BlockTextures::GetBotLeft(unsigned int id, unsigned int face)
{
    Vector2 pos = Vector2Zero();

    //if (id == stone || id == dirt || id == water)
    {
        pos.x = (id % 16) / 16.0f;
        pos.y = 1 - (id/16 + 1) / 16.0f;
    }

    if (id == grass)
    {
        if (face == 20 || face == 100 || face == 120)
        {
            pos.x = 3 / 16.0f;
            pos.y = 1 - 1/16.0f;
        }

        if (face == 40)
        {
            pos.x = 4 / 16.0f;
            pos.y = 1;
        }

        if (face == 60)
        {
            pos.x = 0 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }

        if (face == 80)
        {
            pos.x = 2 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }
    }

    return pos;
}

Vector2 BlockTextures::GetTopRight(unsigned int id, unsigned int face)
{
    Vector2 pos = Vector2Zero();

    //if (id == stone || id == dirt || id == water)
    {
        pos.x = (id % 16 + 1) / 16.0f;
        pos.y = 1 - (id / 16) / 16.0f;
    }

    if (id == grass)
    {
        if (face == 20 || face == 100 || face == 120)
        {
            pos.x = 4 / 16.0f;
            pos.y = 1;
        }

        if (face == 40)
        {
            pos.x = 3 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }

        if (face == 60)
        {
            pos.x = 1 / 16.0f;
            pos.y = 1;
        }

        if (face == 80)
        {
            pos.x = 3 / 16.0f;
            pos.y = 1;
        }
    }
    return pos;
}

Vector2 BlockTextures::GetBotRight(unsigned int id, unsigned int face)
{
    Vector2 pos = Vector2Zero();

    //if (id == stone || id == dirt || id == water)
    {
        pos.x = (id % 16 + 1) / 16.0f;
        pos.y = 1 - (id / 16 + 1) / 16.0f;

    }

    if (id == grass)
    {
        if (face == 20 || face == 40 || face == 100 || face == 120)
        {
            pos.x = 4 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }

        if (face == 40)
        {
            pos.x = 3 / 16.0f;
            pos.y = 1;
        }

        if (face == 60)
        {
            pos.x = 1 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }

        if (face == 80)
        {
            pos.x = 3 / 16.0f;
            pos.y = 1 - 1 / 16.0f;
        }
    }

    return pos;
}
