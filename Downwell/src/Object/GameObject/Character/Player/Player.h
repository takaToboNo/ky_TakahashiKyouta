#pragma once
#include <memory>
#include "Character.h"
#include "PlayerState.h"
#include "PlayerIdle.h"
#include "GunBoots.h"

class Player : public Character
{
private:
	std::unique_ptr<IPlayerState> m_State = std::make_unique<PlayerIdle>();
	std::unique_ptr<IPlayerState> m_NextState = {};

	std::unique_ptr<GunBoots> m_GunBoots = std::make_unique<GunBoots>();

	static constexpr float MOVE_ACCEL = 5000.0f;
	static constexpr float MAX_MOVE_SPEED = 500.0f;
	static constexpr float JUMP_FORCE = 1200.0f;
	static constexpr float JUMP_CUT_RESISTANCE = 0.5f;
	static constexpr float GRAVITY_THRESHOLD_SPEED = 200.0f;
	static constexpr float JUMP_GRAVITY = 2500.0f;
	static constexpr float FALL_GRAVITY = 3500.0f;

	static constexpr float AIR_DRAG = 0.9f;

	bool m_IsGround = false;
	float m_DirectionX = 0.0f;

	bool m_JumpKey = false;
	bool m_OldJumpKey = false;
	bool m_JumpTrigger = false;
	bool m_JumpRelease = false;
	bool m_CanAutoShot = false;

#ifdef _DEBUG
	float m_DebugDrawGravity = 0.0f;
#endif

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
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
		m_Velocity.y = -JUMP_FORCE;
		m_IsGround = false;
	}
	void SetDirectionX(float dir = 0.0f) { m_DirectionX = dir; }
	void AirDrag() { m_Velocity.x *= AIR_DRAG; }
	void StopEnemy(class Enemy);
	void Shoot();

	bool GetJumpTrigger() { return m_JumpTrigger; }
	bool GetJumpRelease() { return m_JumpRelease; }
	
	void SetCanAutoShot(bool can) { m_CanAutoShot = can; }
	bool GetCanAutoShot() { return m_CanAutoShot; }

};