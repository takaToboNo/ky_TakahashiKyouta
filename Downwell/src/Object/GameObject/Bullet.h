#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	static constexpr float BULLET_SPEED = 1000.0f;
	static constexpr float AIR_DRAG = 0.95f;
	static constexpr float MIN_SPEED = 200.0f;

	Vector2 m_Velocity = { 0.0f,0.0f };
	float m_Life = 0.0f;
	int m_Damage = 1;

public:
	Bullet() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

	int GetDamage() { return m_Damage; }
};
