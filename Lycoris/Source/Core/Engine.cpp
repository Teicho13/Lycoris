#include "Core/Engine.h"
#include <SDL.h>

//Util
#include "Utility/DeltaTime.h"
#include "Utility/KeyStates.h"

#include "Graphics/Renderer.h"
#include "Graphics/Window.h"

#include "Managers/SceneManager.h"
#include "R-Type/Scenes/Encounter.h"


DeltaTime dt;

SceneManager sceneManager;

void Engine::Run()
{
	//Initialize project
	if(!Init())
	{
		//Setup went wrong, exit out early
		return;
	}

	while(sceneManager.IsRunning())
	{
		//Calculate new delta time and check for any event updates
		dt.Update();
		HandleEvents();
		
		if(!sceneManager.IsRunning())
		{
			Shutdown();
			return;
		}
		
		Update(dt.GetSeconds());
		Render();
	}

	Shutdown();
}

bool Engine::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	//Set current time
	dt.GetTime();

	if(!Window::Create())
	{
		//Something went wrong with creating the window
		return false;
	}

	if(!Renderer::Create())
	{
		//Something went wrong with creating the renderer
		return false;
	}
	
	//Pointer to keyboard button states
	g_KeyStates = SDL_GetKeyboardState(nullptr);

	//We change to initialize the first scene
	sceneManager.ChangeScene(std::make_unique<Encounter>());
	sceneManager.Start();

	SDL_SetRenderDrawColor(Renderer::GetRenderer(), 27, 146, 214, 255);
	
	return true;
}

void Engine::Update(float deltaTime)
{
	sceneManager.Update(deltaTime);
}

void Engine::Shutdown()
{
	Renderer::Destroy();
	Window::Destroy();
	SDL_Quit();
}

void Engine::Render()
{
	if (!sceneManager.IsRunning()) return;

	//Clear render screen for new frame
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), 27, 146, 214, 255);
	SDL_RenderClear(Renderer::GetRenderer());

	//<-- Render Game Objects here -->
	sceneManager.Render();

	//Render everything to the screen
	SDL_RenderPresent(Renderer::GetRenderer());
}

void Engine::HandleEvents()
{
	sceneManager.HandleEvents();
}


