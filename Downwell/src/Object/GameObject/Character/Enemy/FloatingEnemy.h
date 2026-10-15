#pragma once
#include "Enemy.h"

class Player;

class FloatingEnemy : public Enemy
{
private:
	static constexpr float MAX_MOVE_SPEED = 100.0f;
	static constexpr float KNOCK_BACK_FORCE = 200.0f;
	const Player* m_pPlayer = nullptr;

public:
	FloatingEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

	void Move(Vector2& direction) override;
	void Damage(int damage) override { m_Hp -= damage; }
	void Died() override;
	bool CheckGround() override;

	void SetPlayer(const Player* player) { m_pPlayer = player; }
};