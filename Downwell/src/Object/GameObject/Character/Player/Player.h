#pragma once
#include <memory>
#include "Character.h"
#include "PlayerState.h"
#include "PlayerIdle.h"

class Player : public Character
{
private:
	std::unique_ptr<IPlayerState> m_State = std::make_unique<PlayerIdle>();
	std::unique_ptr<IPlayerState> m_NextState = {};

	static constexpr float kMoveSpeed = 200.0f;
	static constexpr float kMaxMoveSpeed = 500.0f;
	static constexpr float kJumpForce = 1200.0f;
	static constexpr float kGravity = 60.0f;
	static constexpr float kAirDrag = 0.9f;

	bool m_IsGround = false;

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

	void RequestState(std::unique_ptr<IPlayerState> next);
	void SetState();

	void SetGround(bool isGround) { m_IsGround = isGround; }
	bool IsGround() { return m_IsGround; }

	void Move(Vector2& direction) override;
	void Damage(int damage) override;
	void Died() override;
	bool CheckGround() override;

	void Jump()
	{
		m_Velocity.y = -kJumpForce;
		m_IsGround = false;
	}
	void MoveLeftRight(float dir) { m_Velocity.x += kMoveSpeed * dir; }
	void AirDrag() { m_Velocity.x *= kAirDrag; }
	void StopEnemy(class Enemy);
	void Shoot();

};