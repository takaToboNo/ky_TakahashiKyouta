#pragma once
#include "Object.h"
#include "GameHelper.h"
#include "Collider.h"

class Camera;
class GameObjectManager;

class GameObject : public Object
{
protected:
	Vector2 m_Scale = { 1.0f,1.0f };
	Color m_Color = WHITE;
	Collider m_Collider;

	GameObjectManager* m_GameObjectManager = nullptr;

	bool m_IsInCameraArea = false;

public:
	GameObject() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float dt) override;
	virtual void Draw(const Camera& camera);
	virtual void Destroy() override;

	virtual void OnCollision(GameObject* other, const HitInfo& hitInfo) {}

	void SetScale(const Vector2& scale) { m_Scale = scale; }
	void SetColor(Color color) { m_Color = color; }
	const Vector2& GetScale() const { return m_Scale; }
	void SetIsInCameraArea(bool isInCameraArea) { m_IsInCameraArea = isInCameraArea; }

	Collider* GetCollider() { return &m_Collider; }
	HitSide GetHitSide(const HitInfo& hitInfo) const;

	void SetGameObjectManager(GameObjectManager* manager) { m_GameObjectManager = manager; }

	virtual void Activate();
	virtual void Deactivate();
};
