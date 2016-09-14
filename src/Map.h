#pragma once
#include "Actor.h"
class Map :	public Actor {
public:
	Map(vec2 Size = {10, 10});
	~Map();

	vec2 GetSize() { return Size; };

private:
	vec2 Size;
};

