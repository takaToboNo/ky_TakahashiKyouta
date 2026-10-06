#pragma once
#include <memory>
#include "Character.h"

class Player : public Character
{
private:
	static constexpr float kGravity = 10000.0f;
	bool m_IsGround;

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

	bool SetGround(bool isGround) { m_IsGround = isGround; }
	bool IsGround() { return m_IsGround; }

	void Move(Vector2& direction) override;
	void Damage(int damage) override;
	void Died() override;
	bool CheckGround() override;

	void Jump();
	void MoveLeftRight(float);
	void StopEnemy(class Enemy);
	void Shoot();

};