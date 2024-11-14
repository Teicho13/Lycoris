#include <SDL.h>

//Util
#include "Utility/DeltaTime.h"
#include "Utility/KeyStates.h"
#include "Core/Utility/AppGlobals.h"

#include "Core/Engine.h"

#include "Managers/TextureManager.h"
#include "Managers/GameStateManager.h"
#include "Managers/ResourceManager.h"

DeltaTime dt;
GameStateManager stateManager;

Engine::Engine(bool isFullscreen)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	if(isFullscreen)
	{
		m_Window = SDL_CreateWindow("Lycoris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		m_Window = SDL_CreateWindow("Lycoris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);
	}

	//Create renderer for SDL and set default background color
	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
	ResourceManager::GetInstance().SetRenderer(m_Renderer);

	SDL_SetRenderDrawColor(m_Renderer, 27, 146, 214, 255);

	//Pointer to keyboard button states
	g_KeyStates = SDL_GetKeyboardState(nullptr);
}

Engine::~Engine()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Engine::Run()
{
	Init();

	while(stateManager.GetIsRunning())
	{
		dt.Update();
		HandleEvents();
		if(!stateManager.GetIsRunning())
			return;
		Update(dt.GetSeconds());
		Render();
	}
}

void Engine::Init()
{
	//Set current time
	dt.GetTime();

	//Set Renderer for manager
	TextureManager::SetRenderer(m_Renderer);

	stateManager.Init();
}

void Engine::Update(float deltaTime)
{
	stateManager.Update(deltaTime);
}

void Engine::Shutdown()
{
	//<-- Shutdown game elements here -->
	stateManager.Shutdown();
}

void Engine::Render()
{
	if (!stateManager.GetIsRunning()) return;

	//Clear render screen for new frame
	SDL_SetRenderDrawColor(m_Renderer, 27, 146, 214, 255);
	SDL_RenderClear(m_Renderer);

	//<-- Render Game Objects here -->
	stateManager.Render();

	//Render everything to the screen
	SDL_RenderPresent(m_Renderer);
}

void Engine::HandleEvents()
{
	stateManager.HandleEvents();
}


