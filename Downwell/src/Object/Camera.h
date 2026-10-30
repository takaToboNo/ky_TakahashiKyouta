#pragma once
#include "Object.h"

class GameObject;

class Camera : public Object
{
private:
	static constexpr float CAMERA_FRROW_RATE = 0.3f;
	static constexpr float CAMERA_TARGET_OFFSET_Y = 100.0f;

	const GameObject* m_Target = nullptr;

public:
	Camera() = default;
	~Camera() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;

	void SetTarget(const GameObject* target) { m_Target = target; }

	void SnapToTarget();
};