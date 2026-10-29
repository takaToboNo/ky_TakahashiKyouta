#pragma once
#include "Tag.h"
#include "Layer.h"
#include "Vector2.h"

class Object
{
protected:
	Tag m_Tag = Tag::None;
	Layer m_Layer = Layer::None;
	Vector2 m_Position = Vector2::Zero();
	Vector2 m_OldPosition = Vector2::Zero();
	bool m_IsActive = false;
	bool m_IsDead = false;

public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Initialize();
	virtual void Finalize();
	virtual void Update(float dt);
	virtual void Destroy();

	Tag GetTag() const { return m_Tag; }
	Layer GetLayer() const { return m_Layer; }
	void SetPosition(const Vector2& position) { m_Position = position; }
	const Vector2& GetPosition() const { return m_Position; }
	const Vector2& GetOldPosition() const { return m_OldPosition; }
	void SetActive(bool isActive) { m_IsActive = isActive; }
	bool IsActive() const { return m_IsActive; }
	void SetDead(bool isDead) { m_IsDead = isDead; }
	bool IsDead() const { return m_IsDead; }

};