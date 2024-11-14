#pragma once
#include "Core/GameState.h"

class Map;
class PlayState : public GameState
{
public:
	void Init(GameStateManager* manager) override;
	void Tick(GameStateManager* manager,float deltaTime) override;
	void Shutdown() override;
	void Render(GameStateManager* manager) override;
	void HandleEvents(GameStateManager* manager) override;

	static PlayState* Instance() { return &m_PlayState; }

protected:
	PlayState() = default;

private:
	static PlayState m_PlayState;

	Map* m_Level01 = nullptr;
};
