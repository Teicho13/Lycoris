#pragma once
#include <SDL_rect.h>

class Collision
{
public:
    //Axis-Aligned Bounding Box collision
    static bool AABB(const SDL_FPoint PosA, const SDL_Point SizeA, const SDL_FPoint PosB, const SDL_Point SizeB);
};
