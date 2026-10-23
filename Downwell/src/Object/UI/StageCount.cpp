#include "StageCount.h"
#include "StageManager.h"
#include "DxLib.h"

void StageCount::Initialize()
{
	m_Scale = { 0.0f,0.0f };
	m_Color = RED;

	m_Position = { STAGE_LEFT - (m_Scale.x + 330.0f), 70.0f };
}

void StageCount::Finalize()
{
}

void StageCount::Update(float dt)
{
}

void StageCount::Draw()
{
	int stageLoopCount = 0;
	if (m_StageManager)
	{
		stageLoopCount = m_StageManager->GetStageLoopCount();
	}

	int x = static_cast<int>(m_Position.x);
	int y = static_cast<int>(m_Position.y);
	DrawFormatString(x, y, GetColor(RED.r, RED.g, RED.b), "LEVEL : %d", stageLoopCount);
}

void StageCount::Destroy()
{
}
