#pragma once
#include "Enemy.h"

class Camera;

class WalkerEnemy : public Enemy
{
private:
	static constexpr float FALL_GRAVITY = 3500.0f;

public:
	WalkerEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(const Camera& camera) override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

	void Move(Vector2& direction) override;
	void Damage(int damage) override { m_Hp -= damage; }
	void Died() override;
	bool CheckGround() override;
};