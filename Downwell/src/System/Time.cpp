#define NOMINMAX
#include <algorithm>
#include "Time.h"
#include "DxLib.h"
#include "GameHelper.h"

void Time::Initialize()
{
	m_LastCount = GetNowHiPerformanceCount();
	m_DeltaTime = 0.0f;
	m_Accumulator = 0.0f;

	m_UPS = 0.0f;
	m_FPS = 0.0f;
	m_FpsTimer = 0.0f;
	m_FrameCount = 0;
}

void Time::Finalize()
{
}

void Time::Tick()
{
	const LONGLONG now = GetNowHiPerformanceCount();
	const float raw = static_cast<float>(now - m_LastCount) * MICRO_TO_SECOND;

	m_LastCount = now;
	m_DeltaTime = std::min(raw, MAX_DELTA_TIME);
	m_Accumulator += m_DeltaTime;
}

void Time::Update()
{
#ifdef _DEBUG
	m_FpsTimer += FIXED_DELTA_TIME;
	m_FrameCount++;
	if (m_FpsTimer >= 1.0f)
	{
		m_UPS = static_cast<float>(m_FrameCount);
		m_FPS = 1.0f / m_DeltaTime;

		m_FpsTimer -= 1.0f;
		m_FrameCount = 0;
	}
#endif
}

void Time::Draw()
{
#ifdef _DEBUG
	//デバッグ表示
	DrawFormatString(200, 10, GetColor(GRAY.r, GRAY.g, GRAY.b), "UPS : %.2f", m_UPS);
	DrawFormatString(200, 30, GetColor(GRAY.r, GRAY.g, GRAY.b), "FPS : %.2f", m_FPS);
#endif
}

bool Time::ConsumeFixedStep()
{
	if (m_Accumulator < FIXED_DELTA_TIME) return false;

	m_Accumulator -= FIXED_DELTA_TIME;
	return true;
}
