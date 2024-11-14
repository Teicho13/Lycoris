#pragma once

struct SDL_Texture;
struct SDL_Rect;

class Sprite
{
public:
	Sprite(const char* texturePath);
	Sprite(const char* texturePath, const int columns, const int rows);
	~Sprite();

	void SetFrame(int frame);

	SDL_Texture* GetTexture() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetFrames() const;
	int GetCurrentFrame() const;

	void GetSourceRec(SDL_Rect &rec) const;

	void ChangeTexture(const char* texturePath);
	void ResetTexture(const char* texturePath, const int columns, const int rows);

private:
	void CalculateSizeAndFrames(int columns, int rows);

	SDL_Texture* m_Texture = nullptr;
	int m_SpriteWidth = 0;
	int m_SpriteHeight = 0;

	int m_Frames = 0;
	int m_CurrentFrame = 0;
	int m_FrameColumns = 0;
	int m_FrameRows = 0;
};
