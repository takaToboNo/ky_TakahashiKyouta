#pragma once
#include "Tag.h"
#include "Layer.h"
#include "Vector2.h"

class Object
{
protected:
	Tag m_Tag = Tag::None;
	Layer m_Layer = Layer::None;
	Vector2 m_Position = { 0.0f,0.0f };
	bool m_IsActive = false;

public:
	Object() = default;
	virtual ~Object() = default;

	virtual void Initialize();
	virtual void Finalize();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Destroy();

	virtual Layer GetLayer() { return m_Layer; }
	virtual void SetPosition(const Vector2& position) { m_Position = position; }
	virtual const Vector2& GetPosition() const { return m_Position; }
	virtual void SetActive(bool isActive) { m_IsActive = isActive; }
	virtual bool IsActive() const { return m_IsActive; }

};