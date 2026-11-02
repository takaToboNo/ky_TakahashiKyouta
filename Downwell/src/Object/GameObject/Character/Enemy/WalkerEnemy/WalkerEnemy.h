#pragma once
#include <array>
#include <memory>
#include "Enemy.h"
#include "WalkerEnemyState.h"

class Camera;
class Block;

enum class EWalkerEnemyState : int
{
	Move = 0,
	Fall,
	Max
};

class WalkerEnemy : public Enemy
{
private:
	static constexpr int WALKER_ENEMY_MAX_HP = 1;
	static constexpr float WALKER_ENEMY_SIZE = 30.0f;

	static constexpr float FALL_GRAVITY = 2000.0f;
	static constexpr float MAX_FALL_SPEED = 2000.0f;

	static constexpr float MOVE_SPEED = 60.0f;

	static constexpr float FOOT_SENSOR_WIDTH = WALKER_ENEMY_SIZE - 10.0f;
	static constexpr float FOOT_SENSOR_HEIGHT = 20.0f;

	static constexpr float DESPAWN_DISTANCE = 1200.0f;
	
	std::array<std::unique_ptr<IWalkerEnemyState>, static_cast<size_t>(EWalkerEnemyState::Max)> m_WalkerEnemyStateMachine{};
	IWalkerEnemyState* m_CurrentState = nullptr;
	IWalkerEnemyState* m_NextState = nullptr;

	bool m_IsClockwise = true;
	bool m_IsAttached = false;
	Vector2 m_AttachDirection = { 0.0f,-1.0f };
	Vector2 m_MoveDirection = Vector2::Zero();
	Block* m_Block = nullptr;
	Block* m_OldBlock = nullptr;

	std::array<bool, static_cast<size_t>(HitSide::Max)> m_HitSides = { false };

public:
	WalkerEnemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(const Camera& camera) override;
	void DrawDebug() override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;

	void Damage(int damage) override;
	
	void Activate() override;

	void RequestState(EWalkerEnemyState nextState);
	void SetState();

	bool IsAttached() const { return m_IsAttached; }
	bool IsClockwise() const { return m_IsClockwise; }
	const Vector2& GetAttachDirection() const { return m_AttachDirection; }
	void SetMoveDirection(const Vector2& moveDirection) { m_MoveDirection = moveDirection; }

	void UpdateState();
};