#include "Camera.h"
#include "GameObject.h"
#include "GameHelper.h"
#include "MathHelper.h"

float Lerp(float start, float end, float t)
{
	return (end - start) * t + start;
}

void Camera::Initialize()
{
	if(m_Target)
	{
		m_Position.y = m_Target->GetPosition().y - WINDOW_HEIGHT * 0.5f + CAMERA_OFFSET_Y;
	}
}

void Camera::Finalize()
{
}

void Camera::Update(float dt)
{
	if (m_Target)
	{
		const float endY = m_Target->GetPosition().y - WINDOW_HEIGHT * 0.5f + CAMERA_OFFSET_Y;
		m_Position.y = Lerp(m_Position.y, endY, 0.3f);
	}
}