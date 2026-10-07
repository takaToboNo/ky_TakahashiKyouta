#pragma once
#include "Object.h"
#include "GameHelper.h"

class GameObject : public Object
{
protected:
	Vector2 m_Scale = { 1.0f,1.0f };
	Color m_Color = kWhite;

public:
	GameObject() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Destroy() override;

	virtual void SetScale(const Vector2& scale) { m_Scale = scale; }
	void SetColor(Color color) { m_Color = color; }
	virtual const Vector2& GetScale() const { return m_Scale; }

};
