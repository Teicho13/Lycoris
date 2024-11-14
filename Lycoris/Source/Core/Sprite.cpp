#include "Sprite.h"

#include "managers/TextureManager.h"
#include <SDL_rect.h>

#include "Managers/ResourceManager.h"

Sprite::Sprite(const char* texturePath)
{
	m_Texture = TextureManager::CreateTexture(texturePath, m_SpriteWidth, m_SpriteHeight);
	m_Frames = 1;
	m_CurrentFrame = 0;
	m_FrameRows = 1;
	m_FrameColumns = 1;
}

Sprite::Sprite(const char* texturePath, const int columns, const int rows)
{
	m_Texture = TextureManager::CreateTexture(texturePath, m_SpriteWidth, m_SpriteHeight);
	CalculateSizeAndFrames(columns, rows);
	m_CurrentFrame = 0;
}

Sprite::~Sprite()
{
	m_Texture = nullptr;
}

void Sprite::SetFrame(int frame)
{
	//Check if frames are within bounds

	if (frame < 0)
		frame = 0;

	if (frame > m_Frames - 1)
		frame = m_Frames - 1;

	m_CurrentFrame = frame;
}

SDL_Texture* Sprite::GetTexture() const
{
	return m_Texture;
}

int Sprite::GetWidth() const
{
	return m_SpriteWidth;
}

int Sprite::GetHeight() const
{
	return m_SpriteHeight;
}

int Sprite::GetFrames() const
{
	return m_Frames - 1;
}

int Sprite::GetCurrentFrame() const
{
	return m_CurrentFrame;
}

void Sprite::GetSourceRec(SDL_Rect& rec) const
{
	//Set Default assumed values

	int frameW = m_CurrentFrame;
	int frameH = 0;

	//Check if current frame is bigger than max frames per column
	if(m_CurrentFrame >= m_FrameColumns)
	{
		//Check how many times the frame count goes past the max (giving us the rows)
		frameH = m_CurrentFrame / m_FrameColumns;
		//Check remainder for the current column
		frameW = m_CurrentFrame % m_FrameColumns;
	}

	rec.x = (m_SpriteWidth * frameW);
	rec.y = (m_SpriteHeight * frameH);
	rec.w = (m_SpriteWidth);
	rec.h = (m_SpriteHeight);
}

//Changes current sprite's texture
//#Note it does not change the width,height or frames
void Sprite::ChangeTexture(const char* texturePath)
{
	m_Texture = TextureManager::CreateTexture(texturePath);
}

//Changes current sprite's texture
//It will also reset width,height,frames
void Sprite::ResetTexture(const char* texturePath, const int columns, const int rows)
{
	m_Texture = TextureManager::CreateTexture(texturePath, m_SpriteWidth, m_SpriteHeight);
	CalculateSizeAndFrames(columns, rows);
	m_CurrentFrame = 0;
}


//Calculate correct sprite size based on the columns and rows
//Calculate Frames based on the columns and rows
void Sprite::CalculateSizeAndFrames(int columns, int rows)
{
	//Make sure columns and rows are not 0 or below
	if (columns <= 0)
		columns = 1;

	if (rows <= 0)
		rows = 1;

	m_SpriteWidth = m_SpriteWidth / columns;
	m_SpriteHeight = m_SpriteHeight / rows;

	m_Frames = columns * rows;

	m_FrameRows = rows;
	m_FrameColumns = columns;
}