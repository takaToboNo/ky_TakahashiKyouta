#pragma once
#include "Enemy.h"

class WalkerEnemy : public Enemy
{
private:


public:
	WalkerEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void Move(Vector2& direction) override;
	void Damage(int damage) override;
	void Died() override;
	bool CheckGround() override;
};