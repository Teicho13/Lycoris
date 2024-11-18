#pragma once
#include <memory>
#include <SDL_render.h>
#include "Core/Animation.h"
#include "Core/Sprite.h"

class Sprite;
class Entity
{
public:

	Entity(const char* texturePath);
	Entity(const char* texturePath, const int columns, const int rows);
	Entity(const char* texturePath, const int columns, const int rows, float posX, float posY);

	virtual ~Entity() = default;

	virtual void Draw() const;
	virtual void Update(float deltaTime) = 0;
	
	void SetCanDie();
	void Die();

	bool ShouldRemove() const;

	bool IsOutBounds() const;

	void SetPosition(SDL_FPoint newPos);
	void SetPosition(float posX,float posY);
	void SetPosX(float posX);
	void SetPosY(float posY);

	void SetSize(SDL_Point newSize);
	void SetSize(int w, int h);
	void SetWidth(int width);
	void SetHeight(int height);
	
	SDL_FPoint GetPosition() const;
	SDL_Point GetSize() const;

	void Animate();
	void SetFrameDelay(int delay);
	Animation& GetAnimationComponent();

	bool GetIsAnimated() const;
	int GetFrameDelay() const;

	Sprite* GetSprite() const;

private:
	std::unique_ptr<Sprite> m_Sprite;

	SDL_FPoint m_Position {0.f,0.f};
	SDL_Point m_Size {0,0};

	bool m_ShouldDie = false;
	bool m_CanRemove = false;

	bool m_IsAnimated = false;
	//Delay in ms
	int m_FrameDelay = 100;

	Animation m_Animation;
};
