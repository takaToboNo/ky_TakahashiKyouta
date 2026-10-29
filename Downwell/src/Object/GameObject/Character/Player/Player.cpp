#define NOMINMAX
#include "Player.h"
#include "input.h"
#include "FloatingEnemy.h"
#include "WalkerEnemy.h"
#include "AudioManager.h"

#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerJump.h"
#include "PlayerFall.h"
#include "PlayerShot.h"
#include "PlayerDead.h"

//仮
#include "DxLib.h"
#include "Camera.h"
#include <algorithm>
#include "MathHelper.h"

void Player::Initialize()
{
	Character::Initialize();
	m_Tag = Tag::Player;
	m_Layer = Layer::Player;

	m_Position = { WINDOW_WIDTH * 0.5f ,WINDOW_HEIGHT * 0.5f };
	m_Scale = { PLAYER_SIZE_X,PLAYER_SIZE_Y };
	m_IsGround = false;
	m_DirectionX = 0.0f;
	m_MaxHp = 4;
	m_Hp = m_MaxHp;

	m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Idle)] = std::make_unique<PlayerIdle>();
	m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Move)] = std::make_unique<PlayerMove>();
	m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Jump)] = std::make_unique<PlayerJump>();
	m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Fall)] = std::make_unique<PlayerFall>();
	m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Shot)] = std::make_unique<PlayerShot>();
	m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Dead)] = std::make_unique<PlayerDead>();

	m_CurrentState = nullptr;
	m_NextState = m_PlayerStateMachine[static_cast<size_t>(EPlayerState::Idle)].get();

	m_Color = PLAYER_IDLE_COLOR;

	m_GunBoots->Initialize();

	m_CanAutoShot = false;

	m_KnockbackTimer = 0.0f;
	m_InvincibleTimer = 0.0f;
	m_DeathTimer = DEATH_TIME;

	m_GunBoots->SetupBullet(*m_GameObjectManager);
}

void Player::Finalize()
{
	m_GunBoots->Finalize();
	Character::Finalize();
}

void Player::Update(float dt)
{
	Character::Update(dt);

	UpdateState();

	//重力
	const float gravity = (m_Velocity.y < GRAVITY_THRESHOLD_SPEED) ? JUMP_GRAVITY : FALL_GRAVITY;
	m_Velocity.y += gravity * dt;
#ifdef _DEBUG
	m_DebugDrawGravity = gravity;
	m_DebugIsHit = false;
#endif

	bool isReleaseJump = Input::IsRelease(Action::Action);
	if (isReleaseJump && m_Velocity.y < 0.0f)
	{
		m_Velocity *= JUMP_CUT_RESISTANCE;
	}
	if (isReleaseJump) m_CanAutoShot = true;

	if (m_KnockbackTimer <= 0.0f)
	{
		//移動方向
		m_Velocity.x += MOVE_ACCEL * m_DirectionX * dt;

		//速度制限X
		m_Velocity.x = math_helper::clamp(m_Velocity.x, -MAX_MOVE_SPEED, MAX_MOVE_SPEED);
	}

	//速度制限Y
	m_Velocity.y = math_helper::clamp(m_Velocity.y, -MAX_FALL_SPEED, MAX_FALL_SPEED);

	//座標更新
	m_Position += m_Velocity * dt;

	//壁
	m_Position.x = std::max(m_Position.x, STAGE_LEFT);
	m_Position.x = std::min(m_Position.x, STAGE_RIGHT);

	//ノックバック
	if (m_KnockbackTimer > 0.0f)
	{
		m_KnockbackTimer -= dt;
	}

	//無敵時間
	if (m_InvincibleTimer > 0.0f)
	{
		m_InvincibleTimer -= dt;
	}
	else
	{
		m_InvincibleTimer = 0.0f;
	}

	//死んでいるか
	if (m_Hp <= 0 && !m_IsDead)
	{
		AudioManager::GetInstance().StopBGM("Game");
		AudioManager::GetInstance().PlaySE("Dead");
		m_IsDead = true;
	}

	//リザルト画面へ
	if (m_IsDead)
	{
		if (m_DeathTimer > 0.0f)
		{
			m_DeathTimer -= dt;
		}
		else
		{
			m_Velocity.y = 0.0f;
		}
	}

	m_IsGround = false;

	m_GunBoots->Update(dt);
}

void Player::Draw(const Camera& camera)
{
#ifdef _DEBUG
	//デバッグ表示
	const int startPosX = 10;
	const int startPosY = 200;
	DrawFormatString(startPosX, startPosY, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "PosX : %.2f", m_Position.x);
	DrawFormatString(startPosX, startPosY + 20, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "PosY : %.2f", m_Position.y);
	DrawFormatString(startPosX, startPosY + 40, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "VelX : %.2f", m_Velocity.x);
	DrawFormatString(startPosX, startPosY + 60, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "VelY : %.2f", m_Velocity.y);
	DrawFormatString(startPosX, startPosY + 80, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "Gravity : %.2f", m_DebugDrawGravity);
	DrawFormatString(startPosX, startPosY + 100, GetColor(DEBUG_STATUS_COLOR.r, DEBUG_STATUS_COLOR.g, DEBUG_STATUS_COLOR.b), "canAutoShot : %s", m_CanAutoShot ? "true" : "false");
	DrawFormatString(startPosX, startPosY + 120, GetColor(DEBUG_STATUS_COLOR.r, DEBUG_STATUS_COLOR.g, DEBUG_STATUS_COLOR.b), "isGround : %s", m_IsGround ? "true" : "false");
	DrawFormatString(startPosX, startPosY + 140, GetColor(DEBUG_STATUS_COLOR.r, DEBUG_STATUS_COLOR.g, DEBUG_STATUS_COLOR.b), "isHit : %s", m_DebugIsHit ? "true" : "false");
	if (m_CurrentState) DrawFormatString(startPosX, startPosY + 160, GetColor(DEBUG_STATUS_COLOR.r, DEBUG_STATUS_COLOR.g, DEBUG_STATUS_COLOR.b), "State : %s", m_CurrentState->GetStateName());
	DrawFormatString(startPosX, startPosY + 180, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "DeathTimer : %.1f", m_DeathTimer);
	m_GunBoots->Draw();
#endif

	bool blink = (static_cast<int>(m_InvincibleTimer * BLINK_SPEED) % 2) != 0;
	if (blink) return;

	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f) - camera.GetPosition().x);
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f) - camera.GetPosition().y);
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f) - camera.GetPosition().x);
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f) - camera.GetPosition().y);

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);
}

void Player::Destroy()
{
	Character::Destroy();
}

void Player::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
#ifdef _DEBUG
	m_DebugIsHit = true;
#endif
	Tag tag = other->GetTag();
	HitSide hitSide = GetHitSide(hitInfo);

	if (tag == Tag::Block)
	{
		if (hitSide == HitSide::Top)
		{
			m_Velocity.y = 0.0f;
		}
		else if (hitSide == HitSide::Bottom)
		{
			if (!m_StartGameBGM)
			{
				AudioManager::GetInstance().PlayBGM("Game");
				m_StartGameBGM = true;
			}

			m_IsGround = true;
			m_Velocity.y = 0.0f;
		}
		else if (hitSide == HitSide::Left)
		{
			m_Velocity.x = 0.0f;
		}
		else if (hitSide == HitSide::Right)
		{
			m_Velocity.x = 0.0f;
		}

		m_Position -= hitInfo.normal * hitInfo.depth;
	}

	if (m_IsDead) return;

	if (tag == Tag::Enemy)
	{
		FloatingEnemy* floatingEnemy = dynamic_cast<FloatingEnemy*>(other);
		if (floatingEnemy)
		{
			if (hitSide == HitSide::Bottom)
			{	//浮遊敵を踏んだ
				AudioManager::GetInstance().PlaySE("Stomp");
				Reload();
				m_Velocity.y = hitInfo.normal.y * STOMP_KNOCKBACK * -1.0f;
				return;
			}
		}

		if (m_InvincibleTimer > 0.0f) return;

		if (hitSide == HitSide::Bottom)
		{	//縦
			Damage(1);
			m_Velocity.y = std::abs(hitInfo.normal.y) * DAMAGE_KNOCKBACK_Y * -1.0f;
		}
		else
		{	//横
			Damage(1);
			m_IsGround = false;
			m_Velocity.x = hitInfo.normal.x * DAMAGE_KNOCKBACK_X * -1.0f;
			m_Velocity.y = std::abs(hitInfo.normal.y) * DAMAGE_KNOCKBACK_Y * -1.0f;
		}
	}
}

void Player::RequestState(EPlayerState nextState)
{
	m_NextState = m_PlayerStateMachine.at(static_cast<size_t>(nextState)).get();
}

void Player::SetState()
{
	if (m_CurrentState == m_NextState) return;

	if (m_CurrentState) m_CurrentState->Exit(*this);
	m_CurrentState = m_NextState;
	m_NextState = nullptr;
	if (m_CurrentState) m_CurrentState->Enter(*this);
}

void Player::Damage(int damage)
{
	m_Hp -= damage;
	m_KnockbackTimer = KNOCKBACK_TIME;
	m_InvincibleTimer = INVINCIBLE_TIME;

	if (m_Hp > 0)
	{
		AudioManager::GetInstance().PlaySE("Damage");
	}
}

void Player::Jump()
{
	m_Velocity.y = -JUMP_FORCE;
	m_IsGround = false;
}

void Player::Shot(const Vector2& position)
{
	Vector2 offset = Vector2(0.0f, m_Scale.y * 0.5f);
	bool canShot = m_GunBoots->CreateBullet(position + offset);

	if (m_Velocity.y > 0.0f)
	{
		if (canShot)
		{
			//反動
			m_Velocity.y = 0.0f;
		}
		else
		{
			//小反動
			m_Velocity.y *= EMPTY_RECOIL_DAMPING;
			m_CanAutoShot = false;
		}
	}
}

void Player::Reload()
{
	m_GunBoots->Reload();
}

void Player::UpdateState()
{
	if (m_CurrentState) m_CurrentState->Update(*this);
	if (m_NextState) SetState();
}