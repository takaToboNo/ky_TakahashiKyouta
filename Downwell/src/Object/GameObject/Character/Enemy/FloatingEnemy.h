#pragma once
#include "Enemy.h"

class FloatingEnemy : public Enemy
{
private:


public:
	FloatingEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

	void Move(Vector2& direction) override;
	void Damage(int damage) override;
	void Died() override;
	bool CheckGround() override;
};