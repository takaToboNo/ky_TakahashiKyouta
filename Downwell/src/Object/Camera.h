#pragma once
#include "Object.h"

class GameObject;

class Camera : public Object
{
private:
	static constexpr float CAMERA_OFFSET_Y = 100.0f;
	GameObject* m_Target = nullptr;

public:
	Camera() = default;
	~Camera() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;

	void SetTarget(GameObject* target) { m_Target = target; }
};