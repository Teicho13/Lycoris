#include "./managers/TextureManager.h"
#include "./Managers/ResourceManager.h"
#include "Core/Graphics/Renderer.h"

#include <SDL_image.h>

SDL_Texture* TextureManager::CreateTexture(const char* texturePath)
{
	//Create texture
	SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(texturePath);
	SDL_Texture* TempTexture = ResourceManager::GetInstance().GetTexture(texturePath);

	return TempTexture;
}

SDL_Texture* TextureManager::CreateTexture(const char* texturePath, int& imageWidth, int& imageHeight)
{
	//Create texture
	SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(texturePath);
	SDL_Texture* TempTexture = ResourceManager::GetInstance().GetTexture(texturePath);

	imageWidth = surface->w;
	imageHeight = surface->h;

	return TempTexture;
}

void TextureManager::DeleteTexture(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}

void TextureManager::RenderTexture(SDL_Texture* texture, const SDL_FRect* position)
{
	SDL_RenderCopyF(Renderer::GetRenderer(), texture, NULL, position);
}

void TextureManager::RenderTexture(SDL_Texture* texture, const SDL_Rect* sourcePos, const SDL_FRect* position)
{
	SDL_RenderCopyF(Renderer::GetRenderer(), texture, sourcePos, position);
}

void TextureManager::RenderTexture(SDL_Texture* texture, const SDL_Rect* position)
{
	SDL_RenderCopy(Renderer::GetRenderer(), texture, NULL, position);
}

void TextureManager::RenderTexture(SDL_Texture* texture, const SDL_Rect* sourcePos, const SDL_Rect* position)
{
	SDL_RenderCopy(Renderer::GetRenderer(), texture, sourcePos, position);
}

void TextureManager::RenderBox(const float posX, const float posY, const float width, const float height)
{
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), 255, 0, 0, 255);
	SDL_FRect tempRect = SDL_FRect(posX, posY, width, height);
	SDL_RenderDrawRectF(Renderer::GetRenderer(), &tempRect);
}


