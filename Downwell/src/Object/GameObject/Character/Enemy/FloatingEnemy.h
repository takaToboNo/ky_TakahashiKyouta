#pragma once
#include "Enemy.h"

class Player;
class Camera;

class FloatingEnemy : public Enemy
{
private:
	static constexpr int FLOATING_ENEMY_MAX_HP = 3;

	static constexpr float FLOATING_ENEMY_SIZE_X = 45.0f;
	static constexpr float FLOATING_ENEMY_SIZE_Y = 35.0f;

	static constexpr float MAX_MOVE_SPEED = 100.0f;
	static constexpr float DAMAGE_KNOCKBACK = 200.0f;
	static constexpr float NORMAL_KNOCKBACK = 70.0f;
	const Player* m_pPlayer = nullptr;

public:
	FloatingEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(const Camera& camera) override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

	void Damage(int damage) override;
	
	void SetPlayer(const Player* player) { m_pPlayer = player; }

	void Activate() override;
};