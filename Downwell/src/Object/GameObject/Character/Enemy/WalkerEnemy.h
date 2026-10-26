#pragma once
#include "Enemy.h"

class Camera;

class WalkerEnemy : public Enemy
{
private:
	static constexpr int WALKER_ENEMY_MAX_HP = 1;
	static constexpr float WALKER_ENEMY_SIZE = 30.0f;

	static constexpr float FALL_GRAVITY = 2000.0f;
	static constexpr float MAX_FALL_SPEED = 2000.0f;

	bool m_IsGround = false;

public:
	WalkerEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(const Camera& camera) override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

	void Move(Vector2& direction) override;
	void Damage(int damage) override;
	void Died() override;
	bool CheckGround() override;

	void Activate() override;
};