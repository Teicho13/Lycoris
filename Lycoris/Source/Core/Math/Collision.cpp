#include "Collision.h"

bool Collision::AABB(const SDL_FPoint PosA, const SDL_Point SizeA, const SDL_FPoint PosB, const SDL_Point SizeB)
{
    if (PosA.x < PosB.x + static_cast<float>(SizeB.x) &&
        PosA.x + static_cast<float>(SizeA.x) > PosB.x &&
        PosA.y < PosB.y + static_cast<float>(SizeB.y) &&
        PosA.y + static_cast<float>(SizeA.y) > PosB.y)
    {
        return true;
    }
    return false;
}
