#pragma once
#include <string>
#include <unordered_map>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
class ResourceManager
{
public:

	//Delete so you cant make a copy
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;

	static ResourceManager& GetInstance();
	void SetRenderer(SDL_Renderer* renderer);

	SDL_Surface* GetSurface(const std::string& filePath);
	SDL_Texture* GetTexture(const std::string& filePath);

private:
	ResourceManager() = default;

	SDL_Renderer* m_Renderer = nullptr;
	std::unordered_map<std::string, SDL_Surface*> m_Surfaces;
	std::unordered_map<std::string, SDL_Texture*> m_Textures;
};
