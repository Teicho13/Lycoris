#pragma once
#include <SDL_render.h>

class Renderer
{
public:
    static bool Create();
    static void Destroy();

    static void Clear();
    static void Present();

    static SDL_Renderer* GetRenderer();
};

inline SDL_Renderer* g_Renderer = nullptr;