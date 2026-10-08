#include "Player.h"

//仮
#define NOMINMAX
#include "DxLib.h"
#include <algorithm>
#include "MathHelper.h"

void Player::Initialize()
{
	Character::Initialize();
	m_Position = { 600.0f,200.0f };
	m_Scale = { 25.0f,25.0f };
	m_IsGround = false;
	m_DirectionX = 0.0f;

	m_State = std::make_unique<PlayerIdle>();
	m_NextState = std::make_unique<PlayerIdle>();

	m_Color = GREEN;
}

void Player::Finalize()
{
	Character::Finalize();
}

void Player::Update()
{
	float dt = 1.0f / 60.0f;

	if (m_State) m_State->Update(*this);
	if (m_NextState) SetState();

	//重力
	m_Velocity.y += GRAVITY;

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
	}
	else
	{
		m_IsGround = false;
	}

	//壁
	m_Position.x = std::max(m_Position.x, STAGE_LEFT);
	m_Position.x = std::min(m_Position.x, STAGE_RIGHT);
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
}

void Player::Destroy()
{
	Character::Destroy();
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
	(void)damage;
}

void Player::Died()
{
}

bool Player::CheckGround()
{
	return false;
}