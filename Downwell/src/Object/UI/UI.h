#pragma once
#include "Object.h"
#include "GameHelper.h"

class UI : public Object
{
protected:
	Vector2 m_Scale = Vector2::Zero();
	Color m_Color = WHITE;

public:
	UI() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float dt) override;
	virtual void Draw() = 0;
	virtual void Destroy() override;

	void SetScale(const Vector2& scale) { m_Scale = scale; }
	const Vector2& GetScale() const { return m_Scale; }

};