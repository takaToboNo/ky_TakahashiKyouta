#pragma once
#include "GameObject.h"

class Character : public GameObject
{
protected:
	int m_Hp = 1;
	int m_MaxHp = 1;
	float m_MoveSpeed = 1.0f;
	Vector2 m_Velocity = { 0.0f,0.0f };
	Vector2 m_Accel = { 0.0f,0.0f };
	bool m_IsFacingRight = true;

public:
	Character() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Destroy() override;

	virtual void SetVelocity(const Vector2& velocity) { m_Velocity = velocity; }
	virtual const Vector2& GetVelocity() const { return m_Velocity; }
	virtual void SetAccel(const Vector2& accel) { m_Accel = accel; }
	virtual void Move(Vector2& direction) = 0;
	virtual void Damage(int damage) = 0;
	virtual void Died() = 0;
	virtual bool CheckGround() = 0;

};