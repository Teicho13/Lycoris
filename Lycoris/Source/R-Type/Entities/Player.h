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
	~Player() override;

	void Draw() const override;

	void Update(float deltaTime) override;
	bool HandleTileCollision(Map& map) const;

	void SteerShip(float dt);

	//Camera component
	void SetCamera(Camera* camera);
	Camera* GetCamera(Camera* camera) const;

	void HandleMovement(float dt);
	void HandleBoundChecks();

	void SetMovementSpeed(float amount);
	float GetMovementSpeed() const;
	
	void Die() override;
	bool IsAlive() const;

	void ChargeBullet(float dt);
	bool FullyCharged() const;
	bool DisplayCharge() const;
	float GetCurrentCharge() const;

	bool m_InputHeld = false;

private:
	bool m_IsAlive = true;
	float m_MoveSpeed = 500.f;

	Camera* m_CamerRef = nullptr;

	std::unique_ptr<VisualEffect> m_ChargeVFX = nullptr;

	//Charged bullets
	
	bool m_Charged = false;
	float m_Charge = 0;
	float m_ChargeSpeed = 50;
	float m_ChargePosXOffset = 10.f;
	float m_ChargePosYOffset = -5.f;

	//Flight steering animation
	
	int SteerDirection = 0;
	float SteerCurrentVal = 0.f;
	float SteerThreshold = 1.f;
};
