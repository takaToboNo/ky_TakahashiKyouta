#include "Player.h"

//仮
#include <cassert>
#include "Main.h"

void Player::Initialize()
{
	Character::Initialize();
	m_Position = { 200.0f,0.0f };
	m_Scale = { 25.0f,50.0f };
	m_IsGround = false;
}

void Player::Finalize()
{
	Character::Finalize();
}

void Player::Update()
{
	float dt = 1.0f / 60.0f;

	
	//抵抗
	m_Accel *= 0.1f;
	m_Velocity *= 0.92f;

	//重力
	m_Accel.y = kGravity;

	//移動
	if (CheckHitKey(KEY_INPUT_A)) m_Accel.x = -5000.0f;
	if (CheckHitKey(KEY_INPUT_D)) m_Accel.x = 5000.0f;

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) && m_IsGround) m_Accel.y = -200000.0f;

	//速度更新
	m_Velocity += m_Accel * dt;
	//座標更新
	m_Position += m_Velocity * dt;

	//床接地
	if (m_Position.y >= 600.0f)
	{
		m_Position.y = 600.0f;
		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}

	//ループ
	if (m_Position.x < 0.0f) m_Position.x = 1280.0f;
	if (m_Position.x > 1280.0f) m_Position.x = 0.0f;
}

void Player::Draw()
{
	float x1, y1;
	x1 = m_Position.x - (m_Scale.x * 0.5f);
	y1 = m_Position.y - (m_Scale.y * 0.5f);
	float x2, y2;
	x2 = m_Position.x + (m_Scale.x * 0.5f);
	y2 = m_Position.y + (m_Scale.y * 0.5f);

	int result = DrawBox(x1, y1, x2, y2, GetColor(255, 0, 0), TRUE);

	assert(result == 0);
}

void Player::Destroy()
{
	Character::Destroy();
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

void Player::Jump()
{
}

void Player::MoveLeftRight(float)
{
}
