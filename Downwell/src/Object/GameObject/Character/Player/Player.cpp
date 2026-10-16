#define NOMINMAX
#include "Player.h"
#include "input.h"

//仮
#include "DxLib.h"
#include <algorithm>
#include "MathHelper.h"

void Player::Initialize()
{
	Character::Initialize();
	m_Layer = Layer::Player;

	m_Position = { 600.0f,200.0f };
	m_Scale = { 25.0f,25.0f };
	m_IsGround = false;
	m_DirectionX = 0.0f;
	m_Hp = 4;

	m_State = std::make_unique<PlayerIdle>();
	m_NextState = std::make_unique<PlayerIdle>();

	m_Color = GREEN;

	m_GunBoots->Initialize();

	m_CanAutoShot = false;
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
#endif

	bool isReleaseJump = Input::IsRelease(Action::Action);
	if (isReleaseJump && m_Velocity.y < 0.0f)
	{
		m_Velocity *= JUMP_CUT_RESISTANCE;
	}
	if (isReleaseJump) m_CanAutoShot = true;

	//移動方向
	m_Velocity.x += MOVE_ACCEL * m_DirectionX * dt;

	//速度制限
	m_Velocity.x = math_helper::clamp(m_Velocity.x, -MAX_MOVE_SPEED, MAX_MOVE_SPEED);

	//座標更新
	m_Position += m_Velocity * dt;

	//床接地
	if (m_Position.y >= STAGE_BOTTOM)
	{
		m_Position.y = STAGE_BOTTOM;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
		m_CanAutoShot = false;
	}
	else
	{
		m_IsGround = false;
	}

	//壁
	m_Position.x = std::max(m_Position.x, STAGE_LEFT);
	m_Position.x = std::min(m_Position.x, STAGE_RIGHT);

	m_GunBoots->Update(dt);

	m_IsHit = false;
}

void Player::Draw()
{
	int x1, y1;
	x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
	y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
	int x2, y2;
	x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
	y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

	DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);

#ifdef _DEBUG
	//デバッグ表示
	DrawFormatString(10, 10, GetColor(WHITE.r, WHITE.g, WHITE.b), "PosX : %.2f", m_Position.x);
	DrawFormatString(10, 30, GetColor(WHITE.r, WHITE.g, WHITE.b), "PosY : %.2f", m_Position.y);
	DrawFormatString(10, 50, GetColor(WHITE.r, WHITE.g, WHITE.b), "VelX : %.2f", m_Velocity.x);
	DrawFormatString(10, 70, GetColor(WHITE.r, WHITE.g, WHITE.b), "VelY : %.2f", m_Velocity.y);
	DrawFormatString(10, 90, GetColor(WHITE.r, WHITE.g, WHITE.b), "isGround : %s", m_IsGround ? "true" : "false");
	DrawFormatString(10, 110, GetColor(WHITE.r, WHITE.g, WHITE.b), "State : %s", m_State->GetStateName());
	DrawFormatString(10, 130, GetColor(WHITE.r, WHITE.g, WHITE.b), "Gravity : %.2f", m_DebugDrawGravity);
	DrawFormatString(10, 150, GetColor(WHITE.r, WHITE.g, WHITE.b), "canAutoShot : %s", m_CanAutoShot ? "true" : "false");
	DrawFormatString(10, 170, GetColor(WHITE.r, WHITE.g, WHITE.b), "isHit : %s", m_IsHit ? "true" : "false");
	DrawFormatString(10, 190, GetColor(GREEN.r, GREEN.g, GREEN.b), "PlayerHP : %d", m_Hp);
	m_GunBoots->Draw();
#endif
}

void Player::Destroy()
{
	Character::Destroy();
}

void Player::OnCollision(GameObject* other, const HitInfo& hitInfo)
{
	Layer layer = other->GetLayer();
	HitSide hitSide = GetHitSide(hitInfo);

	if (layer == Layer::Enemy)
	{
		m_Velocity = hitInfo.normal * KNOCK_BACK_FORCE * -1.0f;
	}

	if (layer == Layer::Block)
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