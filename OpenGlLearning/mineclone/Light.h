#pragma once

#include "raymath.h"

class Light
{
	Vector3 dir;

public:

	Light(Vector3 dir) : dir(dir) {}

	inline const Vector3& GetDir() { return dir; }

};