#pragma once
#include <memory>
#include "Character.h"
#include "PlayerState.h"
#include "PlayerIdle.h"
#include "GunBoots.h"

class Camera;

class Player : public Character
{
private:
	std::unique_ptr<IPlayerState> m_State = std::make_unique<PlayerIdle>();
	std::unique_ptr<IPlayerState> m_NextState = {};

	std::unique_ptr<GunBoots> m_GunBoots = std::make_unique<GunBoots>();

	static constexpr float MOVE_ACCEL = 5000.0f;
	static constexpr float MAX_MOVE_SPEED = 300.0f;
	static constexpr float MAX_FALL_SPEED = 2000.0f;
	static constexpr float JUMP_FORCE = 700.0f;
	static constexpr float JUMP_CUT_RESISTANCE = 0.5f;
	static constexpr float GRAVITY_THRESHOLD_SPEED = 200.0f;
	static constexpr float JUMP_GRAVITY = 1500.0f;
	static constexpr float FALL_GRAVITY = 2000.0f;

	static constexpr float AIR_DRAG = 0.9f;
	static constexpr float GROUND_DRAG = 0.9f;
	static constexpr float DEAD_DRAG = 0.9f;
	static constexpr float EMPTY_RECOIL_DAMPING = 0.7f;

	static constexpr float DAMAGE_KNOCKBACK_X = 600.0f;
	static constexpr float DAMAGE_KNOCKBACK_Y = 350.0f;
	static constexpr float STOMP_KNOCKBACK = 400.0f;
	static constexpr float KNOCKBACK_TIME = 0.1f;
	static constexpr float INVINCIBLE_TIME = 2.0f;
	static constexpr float BLINK_SPEED = 20.0f;

	static constexpr float DEATH_TIME = 2.0f;

	bool m_IsGround = false;
	float m_DirectionX = 0.0f;

	bool m_CanAutoShot = false;

	float m_KnockbackTimer = 0.0f;
	float m_InvincibleTimer = 0.0f;

	float m_DeathTimer = DEATH_TIME;
	bool m_IsDead = false;

#ifdef _DEBUG
	float m_DebugDrawGravity = 0.0f;
	bool m_DebugIsHit = false;
#endif

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(const Camera& camera) override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

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
	void GroundDrag() { m_Velocity.x *= GROUND_DRAG; }
	void DeadDrag() { m_Velocity.x *= DEAD_DRAG; }
	void StopEnemy(class Enemy);
	void Shot(const Vector2& position);

	void SetCanAutoShot(bool can) { m_CanAutoShot = can; }
	bool GetCanAutoShot() { return m_CanAutoShot; }

	GunBoots* GetGunBoots() const { return m_GunBoots.get(); }
	void Reload() { m_GunBoots->Reload(); }

	float GetKnockbackTimer() { return m_KnockbackTimer; }
	bool IsDead() { return m_IsDead; }
	float GetDeathTimer() { return m_DeathTimer; }
};