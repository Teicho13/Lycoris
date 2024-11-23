#include "ResourceManager.h"
#include "Core/Graphics/Renderer.h"

#include <SDL_surface.h>
#include <SDL_render.h>
#include <SDL_image.h>

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager rm;
	return rm;
}

SDL_Surface* ResourceManager::GetSurface(const std::string& filePath)
{
	//Look for surface.
	const auto search = m_Surfaces.find(filePath);
	if(search != m_Surfaces.end())
	{
		//Return existing surface.
		return m_Surfaces[filePath];
	}

	//Create new Surface and add to the list.
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	m_Surfaces.insert(std::make_pair(filePath,surface));
	return m_Surfaces[filePath];
}

SDL_Texture* ResourceManager::GetTexture(const std::string &filePath)
{
	//Look for texture.
	const auto search = m_Textures.find(filePath);
	if (search != m_Textures.end())
	{
		//return existing texture.
		return m_Textures[filePath];
	}

	//Create new texture and add it to the list.
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), GetSurface(filePath));
	m_Textures.insert(std::make_pair(filePath, texture));
	return m_Textures[filePath];
}
