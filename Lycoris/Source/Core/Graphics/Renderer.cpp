#include "Renderer.h"
#include "Window.h"

#include <iostream>


bool Renderer::Create()
{
    std::cout << "Creating Renderer \n";

    //Create renderer for SDL and set default background color
    g_Renderer = SDL_CreateRenderer(Window::GetWindow(), -1, 0);

    if(g_Renderer == nullptr)
    {
        std::cout << "Failed to create renderer \n";
        return false;
    }

    SDL_SetRenderDrawColor(g_Renderer, 27, 146, 214, 255);

    return true;
}

void Renderer::Destroy()
{
    SDL_DestroyRenderer(g_Renderer);
}

void Renderer::Clear()
{
    //Clear render screen for new frame
    SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_Renderer);
}

void Renderer::Present()
{
    //Render everything to the screen
    SDL_RenderPresent(g_Renderer);
}

SDL_Renderer* Renderer::GetRenderer()
{
    return g_Renderer;
}
