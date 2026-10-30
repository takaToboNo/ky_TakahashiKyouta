#include "Camera.h"
#include "GameObject.h"
#include "GameHelper.h"
#include "MathHelper.h"

void Camera::Initialize()
{
	SnapToTarget();
}

void Camera::Finalize()
{
}

void Camera::Update(float dt)
{
	if (m_Target)
	{
		const float endY = m_Target->GetPosition().y - WINDOW_HEIGHT * 0.5f + CAMERA_TARGET_OFFSET_Y;
		m_Position.y = math_helper::Lerp(m_Position.y, endY, CAMERA_FRROW_RATE);
	}
}

void Camera::SnapToTarget()
{
	if (m_Target)
	{
		m_Position.y = m_Target->GetPosition().y - WINDOW_HEIGHT * 0.5f + CAMERA_TARGET_OFFSET_Y;
	}
}
