#pragma once
#include "Object.h"

class GameObject : public Object
{
protected:
	Vector2 m_Scale;

public:
	GameObject() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Destroy() override;

	virtual void SetScale(Vector2& scale) { m_Scale = scale; }
	virtual const Vector2& GetScale() const { return m_Scale; }

};
