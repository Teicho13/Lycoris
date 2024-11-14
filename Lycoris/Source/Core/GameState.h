#pragma once
#include "Managers/GameStateManager.h"

class GameState
{
public:
	virtual void Init(GameStateManager* manager) = 0;
	virtual void Tick(GameStateManager* manager,float deltaTime) = 0;
	virtual void Shutdown() = 0;
	virtual void Render(GameStateManager* manager) = 0;
	virtual void HandleEvents(GameStateManager* manager) = 0;

	void ChangeState(GameStateManager* manager, const m_GameStates state) { manager->ChangeState(state); }
};
