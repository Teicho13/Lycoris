#pragma once
#include <SDL_rect.h>

class Star
{
public:
    Star();

    void Draw() const;
    void Update(float dt);
    static int GetRandomNumber(int min, int max);

    SDL_FPoint m_Position = { 0.f, 0.f };
    SDL_Color m_Color = { 0, 0, 0, 0 };
    float m_Speed = 50.0f;
};
