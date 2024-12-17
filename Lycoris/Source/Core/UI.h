#pragma once
#include <memory>
#include <SDL_rect.h>

class Sprite;
class UI
{
public:
    UI(const char* texturePath, float posX, float posY);

    void Draw();
    
    void SetPosition(float posX, float posY);
    SDL_FPoint GetPosition() const;
private:
    std::unique_ptr<Sprite> m_Sprite;
    SDL_FPoint m_Position{0,0};
};
