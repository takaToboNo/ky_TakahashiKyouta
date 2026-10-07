#include "Player.h"

//仮
#include <cassert>
#include "DxLib.h"

void Player::Initialize()
{
	Character::Initialize();
	m_Position = { 600.0f,200.0f };
	m_Scale = { 20.0f,20.0f };
	m_IsGround = false;

	m_State = std::make_unique<PlayerIdle>();
	m_NextState = std::make_unique<PlayerIdle>();

	m_Color = kGreen;
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
	m_Velocity.y += kGravity;

	//速度制限
	m_Velocity.x = min(max(m_Velocity.x, -kMaxMoveSpeed), kMaxMoveSpeed);
	
	//座標更新
	m_Position += m_Velocity * dt;

	//床接地
	if (m_Position.y >= kStageBottom)
	{
		m_Position.y = kStageBottom;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}

	//壁
	m_Position.x = max(m_Position.x, kStageLeft);
	m_Position.x = min(m_Position.x, kStageRight);
}

void Player::Draw()
{
	float x1, y1;
	x1 = m_Position.x - (m_Scale.x * 0.5f);
	y1 = m_Position.y - (m_Scale.y * 0.5f);
	float x2, y2;
	x2 = m_Position.x + (m_Scale.x * 0.5f);
	y2 = m_Position.y + (m_Scale.y * 0.5f);

	int result = DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);

	assert(result == 0);
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
	m_State->Enter(*this);
}

void Player::Move(Vector2& direction)
{
}

void Player::Damage(int damage)
{
}

void Player::Died()
{
}

bool Player::CheckGround()
{
	return false;
}