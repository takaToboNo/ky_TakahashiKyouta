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

public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Initialize();
	virtual void Finalize();
	virtual void Update(float dt);
	virtual void Destroy();

	virtual Tag GetTag() { return m_Tag; }
	virtual Layer GetLayer() { return m_Layer; }
	virtual void SetPosition(const Vector2& position) { m_Position = position; }
	virtual const Vector2& GetPosition() const { return m_Position; }
	virtual const Vector2& GetOldPosition() const { return m_OldPosition; }
	virtual void SetActive(bool isActive) { m_IsActive = isActive; }
	virtual bool IsActive() const { return m_IsActive; }

};