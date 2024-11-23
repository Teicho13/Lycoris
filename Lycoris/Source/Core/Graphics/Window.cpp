#include "Window.h"
#include <iostream>

#include "Core/Utility/AppConfig.h"

bool Window::Create()
{
    std::cout << "Creating Window \n";
    
    constexpr auto windowFlag = (AppConfig::Fullscreen) ? SDL_WINDOW_FULLSCREEN : (SDL_WINDOW_SHOWN);

    m_Window = SDL_CreateWindow(AppConfig::Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, AppConfig::Width, AppConfig::Height, windowFlag);

    if(m_Window == nullptr)
    {
        std::cout << "Failed to create Window \n";
        return false;
    }

    return true;
}

void Window::Destroy()
{
    SDL_DestroyWindow(m_Window);
}

SDL_Window* Window::GetWindow()
{
    return m_Window;
}