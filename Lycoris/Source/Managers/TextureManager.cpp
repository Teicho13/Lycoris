#include "./managers/TextureManager.h"
#include "./Managers/ResourceManager.h"
#include "Core/Graphics/Renderer.h"

#include <SDL_image.h>
#include <SDL_pixels.h>

SDL_Texture* TextureManager::CreateTexture(const char* texturePath)
{
	//Look if texture already exists otherwise create a new one.
	SDL_Texture* TempTexture = ResourceManager::GetInstance().GetTexture(texturePath);

	return TempTexture;
}

SDL_Texture* TextureManager::CreateTexture(const char* texturePath, int& imageWidth, int& imageHeight)
{
	//Look if texture already exists otherwise create a new one.
	
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

//Debug draw a box in a specified color
void TextureManager::RenderBox(const float posX, const float posY, const float width, const float height, const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), color.r,color.g,color.b,color.a);
	const SDL_FRect tempRect = SDL_FRect {posX, posY, width, height};
	SDL_RenderDrawRectF(Renderer::GetRenderer(), &tempRect);
}

void TextureManager::RenderBoxFilled(const float posX, const float posY, const float width, const float height,
	const SDL_Color color)
{
	SDL_SetRenderDrawColor(Renderer::GetRenderer(), color.r,color.g,color.b,color.a);
	const SDL_FRect tempRect = SDL_FRect {posX, posY, width, height};
	SDL_RenderFillRectF(Renderer::GetRenderer(), &tempRect);
}


