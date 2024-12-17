#include "UI.h"
#include "Sprite.h"
#include "managers/TextureManager.h"

UI::UI(const char* texturePath, float posX, float posY)
{
    m_Sprite.reset(new Sprite(texturePath));
    m_Position.x = posX;
    m_Position.y = posY;
}

void UI::Draw()
{
    if(m_Sprite != nullptr)
    {
        //Create Variable for the position of the sprite
        const SDL_FRect tempRec(m_Position.x, m_Position.y, static_cast<float>(m_Sprite->GetWidth()), static_cast<float>(m_Sprite->GetHeight()));
        
        //Create temp variable to get the position / size that needs to be rendered
        SDL_Rect tempSource;
        m_Sprite->GetSourceRec(tempSource);
        
        TextureManager::RenderTexture(m_Sprite->GetTexture(), &tempSource, &tempRec);
    }
}

void UI::SetPosition(float posX, float posY)
{
    m_Position.x = posX;
    m_Position.y = posY;
}

SDL_FPoint UI::GetPosition() const
{
    return m_Position;
}
