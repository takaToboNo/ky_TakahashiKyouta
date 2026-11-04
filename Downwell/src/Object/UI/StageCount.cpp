#include "StageCount.h"
#include "StageManager.h"
#include "Renderer.h"

void StageCount::Initialize()
{
	m_Scale = { 0.0f,0.0f };
	m_Color = RED;

	m_Position = { POSITION_X, POSITION_Y };
}

void StageCount::Finalize()
{}

void StageCount::Update(float dt)
{}

void StageCount::Draw(Renderer& renderer)
{
	int stageLoopCount = 0;
	if (m_StageManager)
	{
		stageLoopCount = m_StageManager->GetStageLoopCount();
	}

	renderer.DrawLabelFormat(Space::Screen, m_Position, m_Color, TextAlign::Left, "LEVEL : %d", stageLoopCount);
}

void StageCount::Destroy()
{}
