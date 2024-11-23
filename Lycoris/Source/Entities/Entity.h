#pragma once
#include <memory>
#include <SDL_render.h>
#include "Core/Animation.h"
#include "Core/Sprite.h"
#include "Extras/VisualEffect.h"

class Sprite;
class Entity
{
public:

	//Constructs & destructor
	
	Entity(const char* texturePath);
	Entity(const char* texturePath, const int columns, const int rows);
	Entity(const char* texturePath, const int columns, const int rows, float posX, float posY);
	virtual ~Entity() = default;


	virtual void Draw() const;
	virtual void Update(float deltaTime) = 0;
	void Animate(float dt);
	
	void ChangeHealth(int amount);
	virtual void Explode();
	virtual void Die();
	
	//Setters

	void SetCanDie();

	void SetPosition(SDL_FPoint newPos);
	void SetPosition(float posX,float posY);
	void SetPosX(float posX);
	void SetPosY(float posY);

	void SetSize(SDL_Point newSize);
	void SetSize(int w, int h);
	void SetWidth(int width);
	void SetHeight(int height);

	void SetFrameSpeed(float delay);

	//Getters
	
	SDL_FPoint GetPosition() const;
	SDL_Point GetSize() const;

	bool IsExploding() const;
	
	bool ShouldRemove() const;
	bool IsOutBounds() const;
	
	Sprite* GetSprite() const;
	Animation& GetAnimationComponent();

protected:
	int m_Lives = 1;
	bool m_IsExploding = false;
	std::unique_ptr<VisualEffect> m_DieVFX = nullptr;
	
private:
	std::unique_ptr<Sprite> m_Sprite;

	SDL_FPoint m_Position {0.f,0.f};
	SDL_Point m_Size {0,0};

	bool m_ShouldDie = false;
	bool m_CanRemove = false;

	bool m_IsAnimated = false;
	
	Animation m_Animation;
};
