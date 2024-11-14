#pragma once

struct SDL_Window;
struct SDL_Renderer;

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	void Run();
	bool Init();
	void Update(float deltaTime);
	void Shutdown();

	void Render();
	void HandleEvents();
};
