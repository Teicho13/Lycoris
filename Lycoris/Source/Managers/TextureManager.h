#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_FRect;
struct SDL_Rect;

class TextureManager
{
public:
	static void SetRenderer(SDL_Renderer* renderer);

	static SDL_Texture* CreateTexture(const char* texturePath);
	static SDL_Texture* CreateTexture(const char* texturePath, int &imageWidth, int &imageHeight);
	static void DeleteTexture(SDL_Texture* texture);

	static void RenderTexture(SDL_Texture* texture, const SDL_FRect* position);
	static void RenderTexture(SDL_Texture* texture, const SDL_Rect* sourcePos, const SDL_FRect* position);

	static void RenderTexture(SDL_Texture* texture, const SDL_Rect* position);
	static void RenderTexture(SDL_Texture* texture, const SDL_Rect* sourcePos, const SDL_Rect* position);

	static void RenderBox(const float posX, const float posY, const float width, const float height);

private:
	static inline SDL_Renderer* m_Renderer = nullptr;
};