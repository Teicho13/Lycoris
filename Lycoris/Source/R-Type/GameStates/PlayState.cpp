#include "./R-Type/GameStates/PlayState.h"

#include "Core/Sprite.h"
#include "./R-Type/Entities/Player.h"
#include "R-Type/Map/Map.h"


PlayState PlayState::m_PlayState;

Player* player;

void PlayState::Init(GameStateManager* manager)
{
	player = new Player("Assets/Games/R-Type/Textures/Player/Player.png",5,1);
	player->GetSprite()->SetFrame(2);

	m_Level01 = new Map("./Assets/Games/R-Type/MapData/Level01.csv", "Assets/Games/R-Type/Textures/Maps/Level01Tiles64.png", 22, 20);

}

void PlayState::Tick(GameStateManager* manager, float deltaTime)
{
	player->Update(deltaTime);
}

void PlayState::Shutdown()
{
	delete player;
	delete m_Level01;
}

void PlayState::Render(GameStateManager* manager)
{
	m_Level01->DrawMap();
	player->Draw();
}

void PlayState::HandleEvents(GameStateManager* manager)
{
}