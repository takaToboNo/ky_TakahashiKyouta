#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	static constexpr float BULLET_SPEED = 1000.0f;

	Vector2 m_Velocity = { 0.0f,0.0f };
	float m_Life = 0.0f;
	int m_Damage = 0;

public:
	Bullet() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

	int GetDamage() { return m_Damage; }
};
