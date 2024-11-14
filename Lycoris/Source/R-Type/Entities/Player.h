#pragma once
#include "./Entities/Entity.h"

class Map;
class Camera;
class VisualEffect;

class Player : public Entity
{
public:
	Player(const char* texturePath);
	Player(const char* texturePath, const int columns, const int rows);

	void Draw() const override;

	void Update(float deltaTime) override;
	bool HandleTileCollision(Map* map) const;

	void SetCamera(Camera* camera);
	Camera* GetCamera(Camera* camera) const;

	void HandleMovement(float dt);
	void HandleBoundChecks();

	void SetMovementSpeed(float amount);
	float GetMovementSpeed() const;

	void Die();
	void Explode();
	bool IsExploding() const;
	bool IsAlive() const;

	void ChargeBullet(float dt);
	bool FullyCharged() const;

	bool m_InputHeld = false;

private:
	bool m_IsAlive = true;
	bool m_IsExploding = false;
	float m_MoveSpeed = 500.f;

	Camera* m_CamerRef = nullptr;

	std::unique_ptr<VisualEffect> m_ChargeVFX = nullptr;
	std::unique_ptr<VisualEffect> m_DieVFX = nullptr;

	bool m_Charged = false;
	float m_Charge = 0;
	float m_ChargeSpeed = 50;
	float m_ChargePosXOffset = 10.f;
	float m_ChargePosYOffset = -5.f;
};
