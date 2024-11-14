#pragma once
#include <memory>
#include "./Core/Animation.h"


class Player;
class Sprite;
class VisualEffect
{
public:
	VisualEffect(const char* texturePath, const int columns, const int rows, float posX, float posY, bool looping, bool startOn = true, Player* player = nullptr);
	void Callback();
	void Draw();
	void Update();

	void SetPosX(float newX);
	void SetPosY(float newY);

	Sprite* GetSprite() const;
	Animation* GetAnimation();

	void SetPlayer(Player* player);

private:
	Animation m_Animation;
	std::unique_ptr<Sprite> m_Sprite;

	Player* m_Player = nullptr;

	float m_PosX = 0.f;
	float m_PosY = 0.f;
	int m_Width = 0;
	int m_Height = 0;
};
