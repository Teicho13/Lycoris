#include "Managers/GameStateManager.h"

#include "Core/GameState.h"
#include "R-Type/GameStates/PlayState.h"


void GameStateManager::Init()
{
	//Load Play State singelton
	m_States.push_back(PlayState::Instance());
	m_States.back()->Init(this);

	//Initialize is done and set game to run
	m_IsRunning = true;
}

void GameStateManager::Update(const float deltaTime)
{
	m_States.back()->Tick(this, deltaTime);
}

void GameStateManager::Shutdown()
{
	m_IsRunning = false;
	m_States.back()->Shutdown();
}

void GameStateManager::Render()
{
	m_States.back()->Render(this);
}

void GameStateManager::HandleEvents()
{
	m_States.back()->HandleEvents(this);
}

void GameStateManager::ChangeState(m_GameStates state)
{
	GameState* newState;

	switch (state)
	{
	case m_GameStates::MENU :
		newState = PlayState::Instance();
		break;

	case m_GameStates::PLAY :
		newState = PlayState::Instance();
		break;

	case m_GameStates::END :
		newState = PlayState::Instance();
		break;
	}

	//Remove current state
	if (!m_States.empty())
	{
		//call Shutdown for current state before removal to clean up.
		m_States.back()->Shutdown();
		m_States.pop_back();
	}

	m_States.push_back(newState);
	m_States.back()->Init(this);

}

void GameStateManager::RemoveState()
{
	//Remove current state
	if (!m_States.empty())
	{
		//call Shutdown for current state before removal to clean up.
		m_States.back()->Shutdown();
		m_States.pop_back();
	}
}

bool GameStateManager::GetIsRunning() const
{
	return m_IsRunning;
}
