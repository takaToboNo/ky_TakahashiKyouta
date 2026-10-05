#pragma once
#include "GameObject.h"

class Character : public GameObject
{
protected:
	int m_Hp;
	int m_MaxHp;
	float m_MoveSpeed;
	Vector2 m_Velocity;
	Vector2 m_Accel;
	bool m_IsFacingRight;

public:
	Character() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Destroy() override;

	virtual void SetVelocity(Vector2& velocity) { m_Velocity = velocity; }
	virtual void Move(Vector2& direction) = 0;
	virtual void Damage(int damage) = 0;
	virtual void Died() = 0;
	virtual bool CheckGround() = 0;

};