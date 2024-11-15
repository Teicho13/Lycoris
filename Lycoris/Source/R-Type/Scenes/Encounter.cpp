#include "Encounter.h"
#include "Managers/SceneManager.h"

#include "R-Type/Map/Map.h"

#include <SDL_events.h>


void Encounter::Init()
{
    m_Level01 = new Map("./Assets/Games/R-Type/MapData/Level01.csv", "Assets/Games/R-Type/Textures/Maps/Level01Tiles64.png", 22, 20);
}

void Encounter::Tick(float dt)
{
}

void Encounter::Render()
{
}

void Encounter::Destroy()
{
}

void Encounter::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            //Window "X" is clicked
        case SDL_QUIT:
                SceneManager::GetSceneManager()->Shutdown();
            break;

            //key is pressed
            case SDL_KEYDOWN:
                //If Escape is clicked exit out
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SceneManager::GetSceneManager()->Shutdown();
                    return;
                }
            break;
        }
		
    }
}
