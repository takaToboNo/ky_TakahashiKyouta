#define NOMINMAX
#include "Player.h"
#include "input.h"
#include "FloatingEnemy.h"
#include "WalkerEnemy.h"

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

	m_Position = { WINDOW_WIDTH * 0.5f ,200.0f };
	m_Scale = { PLAYER_SIZE_X,PLAYER_SIZE_Y };
	m_IsGround = false;
	m_DirectionX = 0.0f;
	m_Hp = 4;

	m_State = std::make_unique<PlayerIdle>();
	m_NextState = std::make_unique<PlayerIdle>();

	m_Color = GREEN;

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

	if (m_State) m_State->Update(*this);
	if (m_NextState) SetState();

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

	if(m_KnockbackTimer <= 0.0f)
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
	if (m_Hp <= 0) m_IsDead = true;

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
	DrawFormatString(10, 10, GetColor(GRAY.r, GRAY.g, GRAY.b), "PosX : %.2f", m_Position.x);
	DrawFormatString(10, 30, GetColor(GRAY.r, GRAY.g, GRAY.b), "PosY : %.2f", m_Position.y);
	DrawFormatString(10, 50, GetColor(GRAY.r, GRAY.g, GRAY.b), "VelX : %.2f", m_Velocity.x);
	DrawFormatString(10, 70, GetColor(GRAY.r, GRAY.g, GRAY.b), "VelY : %.2f", m_Velocity.y);
	DrawFormatString(10, 90, GetColor(GRAY.r, GRAY.g, GRAY.b), "Gravity : %.2f", m_DebugDrawGravity);
	DrawFormatString(10, 110, GetColor(GRAY.r, GRAY.g, GRAY.b), "canAutoShot : %s", m_CanAutoShot ? "true" : "false");
	DrawFormatString(10, 130, GetColor(GRAY.r, GRAY.g, GRAY.b), "isGround : %s", m_IsGround ? "true" : "false");
	DrawFormatString(10, 150, GetColor(GRAY.r, GRAY.g, GRAY.b), "isHit : %s", m_DebugIsHit ? "true" : "false");
	DrawFormatString(10, 170, GetColor(GRAY.r, GRAY.g, GRAY.b), "State : %s", m_State->GetStateName());
	DrawFormatString(10, 190, GetColor(GREEN.r, GREEN.g, GREEN.b), "PlayerHP : %d", m_Hp);
	DrawFormatString(10, 210, GetColor(RED.r, RED.g, RED.b), "DeathTimer : %.1f", m_DeathTimer);
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

void Player::RequestState(std::unique_ptr<IPlayerState> next)
{
	m_NextState = std::move(next);
}

void Player::SetState()
{
	if (m_State == m_NextState) return;

	if (m_State) m_State->Exit(*this);
	m_State = std::move(m_NextState);
	if (m_State) m_State->Enter(*this);
}

void Player::Move(Vector2& direction)
{
	(void)direction;
}

void Player::Damage(int damage)
{
	m_Hp -= damage;
	m_KnockbackTimer = KNOCKBACK_TIME;
	m_InvincibleTimer = INVINCIBLE_TIME;
}

void Player::Died()
{
}

bool Player::CheckGround()
{
	return false;
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