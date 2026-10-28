#include "WalkerEnemy.h"
#include "Bullet.h"
#include "Player.h"
#include "AudioManager.h"

#include "WalkerEnemyMove.h"
#include "WalkerEnemyFall.h"
#include "Block.h"

#include <cassert>
#include "DxLib.h"
#include "Camera.h"
#include "MathHelper.h"

void WalkerEnemy::Initialize()
{
	Enemy::Initialize();
	m_Position = { 500.0f,650.0f };
	m_Scale = { WALKER_ENEMY_SIZE,WALKER_ENEMY_SIZE };
	m_Color = ENEMY_COLOR;
	m_Hp = 1;
	m_IsClockwise = rand() % 2 == 0;
	m_IsAttached = false;

	m_WalkerEnemyStateMachine[static_cast<size_t>(EWalkerEnemyState::Move)] = std::make_unique<WalkerEnemyMove>();
	m_WalkerEnemyStateMachine[static_cast<size_t>(EWalkerEnemyState::Fall)] = std::make_unique<WalkerEnemyFall>();

	m_CurrentState = m_WalkerEnemyStateMachine[static_cast<size_t>(EWalkerEnemyState::Fall)].get();
	m_NextState = m_WalkerEnemyStateMachine[static_cast<size_t>(EWalkerEnemyState::Fall)].get();
}

void WalkerEnemy::Finalize()
{
	Enemy::Finalize();
}

void WalkerEnemy::Update(float dt)
{
	Enemy::Update(dt);

	if (m_CurrentState) m_CurrentState->Update(*this);
	if (m_NextState) SetState();

	if (!m_IsAttached)
	{
		if (!m_Block && m_OldBlock)
		{	//外周移動補間

			if (m_AttachDirection.x != 0.0f && m_OldBlock->IsActive())
			{	//横面から床面
				const float combineHalfHeight = (m_OldBlock->GetScale().y + m_Scale.y) * 0.5f;
				const float directionY = m_AttachDirection.x * (m_IsClockwise ? 1.0f : -1.0f);
				//通り過ぎた分を補間
				m_Position.y = m_OldBlock->GetPosition().y + combineHalfHeight * directionY;

				m_Position.x -= m_AttachDirection.x;
			}
			else if (m_AttachDirection.y != 0.0f && m_OldBlock->IsActive())
			{	//床面から横面
				const float combineHalfWidth = (m_OldBlock->GetScale().x + m_Scale.x) * 0.5f;
				const float directionX = m_AttachDirection.y * (m_IsClockwise ? -1.0f : 1.0f);
				//通り過ぎた分を補間
				m_Position.x = m_OldBlock->GetPosition().x + combineHalfWidth * directionX;

				m_Position.y -= m_AttachDirection.y;
			}
			else
			{
				//ブロックが破壊された
			}

			m_IsClockwise ? m_AttachDirection.RotateClockwise90() : m_AttachDirection.RotateCounterClockwise90();
		}
		else
		{
			//重力
			const float gravity = (m_IsAttached) ? 0.0f : FALL_GRAVITY;
			m_Velocity.x = 0.0f;
			m_Velocity.y += gravity * dt;

			//速度制限Y
			m_Velocity.y = math_helper::clamp(m_Velocity.y, -MAX_FALL_SPEED, MAX_FALL_SPEED);
		}
	}
	else
	{
		if (m_IsClockwise)
		{	//この条件の時だけ止まってしまうため無理やり位置を補正する
			if (m_HitSides[static_cast<size_t>(HitSide::Bottom)] && m_HitSides[static_cast<size_t>(HitSide::Right)])
			{
				m_Position.y -= 1.0f;
			}
			if (m_HitSides[static_cast<size_t>(HitSide::Top)] && m_HitSides[static_cast<size_t>(HitSide::Right)])
			{
				m_Position.x -= 1.0f;
			}
			if (m_HitSides[static_cast<size_t>(HitSide::Top)] && m_HitSides[static_cast<size_t>(HitSide::Left)])
			{
				m_Position.y += 1.0f;
			}
		}
		else
		{	//この条件の時だけ止まってしまうため無理やり位置を補正する
			if (m_HitSides[static_cast<size_t>(HitSide::Bottom)] && m_HitSides[static_cast<size_t>(HitSide::Left)])
			{
				m_Position.y -= 1.0f;
			}
			if (m_HitSides[static_cast<size_t>(HitSide::Top)] && m_HitSides[static_cast<size_t>(HitSide::Left)])
			{
				m_Position.x += 1.0f;
			}
			if (m_HitSides[static_cast<size_t>(HitSide::Top)] && m_HitSides[static_cast<size_t>(HitSide::Right)])
			{
				m_Position.y += 1.0f;
			}
		}

		//移動
		m_Velocity = m_MoveDirection * MOVE_SPEED;
	}

	if (m_CameraErea)
	{
		//座標更新
		m_Position += m_Velocity * dt;
	}
	else
	{
		m_Velocity = Vector2::Zero();
	}

	m_IsAttached = false;

	m_OldBlock = m_Block;
	m_Block = nullptr;
	m_HitSides.fill(false);

	//死亡
	if (m_Hp <= 0 && !m_IsDead)
	{
		AudioManager::GetInstance().PlaySE("EnemyDead");
		m_IsDead = true;
	}

	//死んでいるならプール状態
	if (m_IsDead)
	{
		m_IsActive = false;
	}

	if (m_Position.x < STAGE_LEFT || m_Position.x > STAGE_RIGHT)
	{
		Deactivate();
	}
}

void WalkerEnemy::Draw(const Camera& camera)
{
	const Vector2& pos = camera.GetPosition();
	const float CAMERA_MARGIN = 100.0f;	//カメラ範囲より少し広い領域にいるとき、動かない

	if (m_Position.y >= pos.y - CAMERA_MARGIN && m_Position.y <= pos.y + WINDOW_HEIGHT + CAMERA_MARGIN)
	{
		m_CameraErea = true;
	}
	else
	{
		m_CameraErea = false;
	}

	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - pos.x);
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - pos.y);
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - pos.x);
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - pos.y);

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);

#ifdef _DEBUG
	int centerX = static_cast<int>(m_Position.x - pos.x);
	int centerY = static_cast<int>(m_Position.y - pos.y);
	int attachDirX = static_cast<int>(m_AttachDirection.x) * 20;
	int attachDirY = static_cast<int>(m_AttachDirection.y) * 20;
	DrawLine(centerX, centerY, centerX + attachDirX, centerY + attachDirY, GetColor(DEBUG_STATUS_COLOR.r, DEBUG_STATUS_COLOR.g, DEBUG_STATUS_COLOR.b));
	int moveDirX = static_cast<int>(m_MoveDirection.x) * 40;
	int moveDirY = static_cast<int>(m_MoveDirection.y) * 40;
	DrawLine(centerX, centerY, centerX + moveDirX, centerY + moveDirY, GetColor(WHITE.r, WHITE.g, WHITE.b));
	for (int i = 0; i < static_cast<size_t>(HitSide::Max); i++)
	{
		const int startPosX = 1000;
		const int startPosY = 500;
		DrawFormatString(startPosX, startPosY + i * 20, GetColor(DEBUG_STATUS_COLOR.r, DEBUG_STATUS_COLOR.g, DEBUG_STATUS_COLOR.b), "HitSides : %s", m_HitSides[i] ? "true" : "false");
	}
#endif
}

void WalkerEnemy::Destroy()
{
	Enemy::Destroy();
}

void WalkerEnemy::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Tag tag = other->GetTag();
	HitSide hitSide = other->GetHitSide(hitInfo);

	if (tag == Tag::Block)
	{
		if (hitSide == HitSide::Top)
		{
			m_AttachDirection = { 0.0f,1.0f };
			m_HitSides[static_cast<size_t>(HitSide::Top)] = true;
		}
		if (hitSide == HitSide::Bottom)
		{
			m_AttachDirection = { 0.0f,-1.0f };
			m_HitSides[static_cast<size_t>(HitSide::Bottom)] = true;
		}
		if (hitSide == HitSide::Left)
		{
			m_AttachDirection = { 1.0f,0.0f };
			m_HitSides[static_cast<size_t>(HitSide::Left)] = true;
		}
		if (hitSide == HitSide::Right)
		{
			m_AttachDirection = { -1.0f,0.0f };
			m_HitSides[static_cast<size_t>(HitSide::Right)] = true;
		}

		m_IsAttached = true;
		m_Position -= hitInfo.normal * hitInfo.depth;

		if (dynamic_cast<Block*>(other))
		{
			m_Block = static_cast<Block*>(other);
		}
	}

	if (tag == Tag::Bullet)
	{
		assert(dynamic_cast<Bullet*>(other));
		if (!dynamic_cast<Bullet*>(other)) return;

		Bullet* bullet = static_cast<Bullet*>(other);
		Damage(bullet->GetDamage());
	}
}

void WalkerEnemy::Move(Vector2& direction)
{
	(void)direction;
}

void WalkerEnemy::Damage(int damage)
{
	AudioManager::GetInstance().PlaySE("EnemyHit");
	m_Hp -= damage;
}

void WalkerEnemy::Died()
{
}

bool WalkerEnemy::CheckGround()
{
	return false;
}

void WalkerEnemy::Activate()
{
	Character::Activate();
	m_Hp = WALKER_ENEMY_MAX_HP;
}

void WalkerEnemy::RequestState(EWalkerEnemyState nextState)
{
	m_NextState = m_WalkerEnemyStateMachine.at(static_cast<size_t>(nextState)).get();
}

void WalkerEnemy::SetState()
{
	if (m_CurrentState == m_NextState) return;

	if (m_CurrentState) m_CurrentState->Exit(*this);
	m_CurrentState = m_NextState;
	m_NextState = nullptr;
	if (m_CurrentState) m_CurrentState->Enter(*this);
}
