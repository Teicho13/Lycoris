#include "Star.h"
#include "Core/Utility/AppConfig.h"

#include "SDL_rect.h"

#include <random>

#include "managers/TextureManager.h"
typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(1, AppConfig::Width);

Star::Star()
{
    m_Color.r = static_cast<Uint8>(GetRandomNumber(1,255));
    m_Color.g = static_cast<Uint8>(GetRandomNumber(1,255));
    m_Color.b = static_cast<Uint8>(GetRandomNumber(1,255));

    m_Position.x = static_cast<float>(GetRandomNumber(1,AppConfig::Width));
    m_Position.y = static_cast<float>(GetRandomNumber(1,AppConfig::Height));

    m_Speed =  static_cast<float>(GetRandomNumber(25,50));
}

void Star::Draw() const
{
    TextureManager::RenderBox(static_cast<float>(m_Position.x), static_cast<float>(m_Position.y), 2,2, m_Color);
}

void Star::Update(float dt)
{
    m_Position.x -= m_Speed * dt;
    if(m_Position.x - 2 < 0)
    {
        m_Position.x = AppConfig::Width + 2;
    }
};

int Star::GetRandomNumber(int min, int max)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max);

    return distr(gen);
}
