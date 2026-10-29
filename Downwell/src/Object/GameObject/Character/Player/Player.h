#pragma once
#include <array>
#include <memory>
#include "Character.h"
#include "GunBoots.h"
#include "PlayerState.h"

class Camera;

enum class EPlayerState : int
{
	Idle = 0,
	Move,
	Jump,
	Fall,
	Shot,
	Dead,
	Max
};

class Player : public Character
{
private:
	std::array<std::unique_ptr<IPlayerState>, static_cast<size_t>(EPlayerState::Max)> m_PlayerStateMachine{};
	IPlayerState* m_CurrentState = nullptr;
	IPlayerState* m_NextState = nullptr;

	std::unique_ptr<GunBoots> m_GunBoots = std::make_unique<GunBoots>();

	static constexpr float PLAYER_SIZE_X = 30.0f;
	static constexpr float PLAYER_SIZE_Y = 40.0f;

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

	bool m_StartGameBGM = false;

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

	void RequestState(EPlayerState nextState);
	void SetState();

	void SetGround(bool isGround) { m_IsGround = isGround; }
	bool IsGround() const { return m_IsGround; }

	void Damage(int damage) override;

	void Jump();
	void SetDirectionX(float dir = 0.0f) { m_DirectionX = dir; }
	void AirDrag() { m_Velocity.x *= AIR_DRAG; }
	void GroundDrag() { m_Velocity.x *= GROUND_DRAG; }
	void DeadDrag() { m_Velocity.x *= DEAD_DRAG; }
	void Shot(const Vector2& position);

	void SetCanAutoShot(bool can) { m_CanAutoShot = can; }
	bool GetCanAutoShot() const { return m_CanAutoShot; }

	GunBoots* GetGunBoots() const { return m_GunBoots.get(); }
	void Reload();

	float GetKnockbackTimer() const { return m_KnockbackTimer; }
	float GetDeathTimer() const { return m_DeathTimer; }
	bool IsDead() const { return m_IsDead; }

	void UpdateState();
};