#include <algorithm>
#include "Timer.h"
#include "DxLib.h"
#include "imgui.h"

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
	m_DeltaTime = (std::min)(raw, MAX_DELTA_TIME);
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
	if (ImGui::Begin("Performance"))
	{
		ImGui::Text("FPS");
		ImGui::SameLine(100.0f);
		ImGui::Text("%.1f", m_FPS);

		ImGui::Text("UPS");
		ImGui::SameLine(100.0f);
		ImGui::Text("%.1f", m_UPS);
	}

	ImGui::End();
#endif
}

bool Timer::ConsumeFixedStep()
{
	if (m_Accumulator < FIXED_DELTA_TIME) return false;

	m_Accumulator -= FIXED_DELTA_TIME;
	return true;
}
