#include "ResultUI.h"
#include "Player.h"
#include "StageManager.h"
#include "DxLib.h"
#include "GameHelper.h"

void ResultUI::Initialize()
{
	m_Position = { WINDOW_WIDTH * 0.5f,WINDOW_HEIGHT * 0.5f };
	m_Scale = { MAP_SIZE_X * TILE_SIZE, MAP_SIZE_Y * TILE_SIZE * 0.5f };
}

void ResultUI::Finalize()
{
}

void ResultUI::Update(float dt)
{
}

void ResultUI::Draw()
{
	if (!m_Player) return;
	if (!m_StageManager) return;

	if (m_Player->GetDeathTimer() <= 0.0f)
	{
		int x1, y1;
		x1 = static_cast<int>(m_Position.x - (m_Scale.x * 0.5f));
		y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
		int x2, y2;
		x2 = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f));
		y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));

		DrawBox(x1, y1, x2, y2, GetColor(0, 0, 0), TRUE);

		int x = static_cast<int>(m_Position.x) - 50;//Х╢ОЪВ╠И╩ТuТ▓Ро
		int y = static_cast<int>(m_Position.y) - 100;
		DrawString(x, y, "GAME OVER", GetColor(RED.r, RED.g, RED.b));
		DrawFormatString(x, y + 50, GetColor(RED.r, RED.g, RED.b), "LEVEL : %d", m_StageManager->GetStageLoopCount());
	}
}

void ResultUI::Destroy()
{
}
