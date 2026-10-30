#define NOMINMAX
#include <algorithm>
#include "Timer.h"
#include "DxLib.h"
#include "GameHelper.h"

void Timer::Initialize()
{
	m_LastCount = GetNowHiPerformanceCount();
	m_DeltaTime = 0.0f;
	m_Accumulator = 0.0f;

	m_UPS = 0.0f;
	m_FPS = 0.0f;
	m_FpsTimer = 0.0f;
	m_FrameCount = 0;
}

void Timer::Finalize()
{
}

void Timer::Tick()
{
	const LONGLONG now = GetNowHiPerformanceCount();
	const float raw = static_cast<float>(now - m_LastCount) * MICRO_TO_SECOND;

	m_LastCount = now;
	m_DeltaTime = std::min(raw, MAX_DELTA_TIME);
	m_Accumulator += m_DeltaTime;
}

void Timer::Update()
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

void Timer::Draw()
{
#ifdef _DEBUG
	//デバッグ表示
	const int startPosX = 10;
	const int startPosY = 100;
	DrawFormatString(startPosX, startPosY, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "UPS : %.2f", m_UPS);
	DrawFormatString(startPosX, startPosY + 20, GetColor(DEBUG_NORMAL_COLOR.r, DEBUG_NORMAL_COLOR.g, DEBUG_NORMAL_COLOR.b), "FPS : %.2f", m_FPS);
#endif
}

bool Timer::ConsumeFixedStep()
{
	if (m_Accumulator < FIXED_DELTA_TIME) return false;

	m_Accumulator -= FIXED_DELTA_TIME;
	return true;
}

bool Timer::HasRemainingStep()
{
	return m_Accumulator >= FIXED_DELTA_TIME;
}

void Timer::DiscardRemainingSteps()
{
	m_Accumulator = 0.0f;
}
