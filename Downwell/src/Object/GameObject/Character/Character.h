#pragma once
#include "GameObject.h"

class Character : public GameObject
{
protected:
	int m_Hp = 1;
	int m_MaxHp = 1;
	float m_MoveSpeed = 1.0f;
	Vector2 m_Velocity = Vector2::Zero();
	Vector2 m_SpawnPosition = Vector2::Zero();
	bool m_IsFacingRight = true;

public:
	Character() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;

	void SetVelocity(const Vector2& velocity) { m_Velocity = velocity; }
	const Vector2& GetVelocity() const { return m_Velocity; }
	void SetSpawnPosition(const Vector2& spawnPosition);

	virtual void Damage(int damage) = 0;
	
	virtual void Activate() override;

	int GetMaxHp() { return m_MaxHp; }
	int GetHp() { return m_Hp; }

};