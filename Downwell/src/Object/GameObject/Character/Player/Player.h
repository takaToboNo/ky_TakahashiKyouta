#pragma once
#include <memory>
#include "Character.h"
#include "PlayerState.h"
#include "PlayerIdle.h"

class Player : public Character
{
private:
	std::unique_ptr<IPlayerState> m_State = std::make_unique<PlayerIdle>();

	static constexpr float kJumpForce = 2000.0f;
	static constexpr float kGravity = 10000.0f;

	bool m_IsGround = false;


public:
	int m_R = 0;
	int m_G = 0;
	int m_B = 0;

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

	void SetState(std::unique_ptr<IPlayerState> next);

	void SetGround(bool isGround) { m_IsGround = isGround; }
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