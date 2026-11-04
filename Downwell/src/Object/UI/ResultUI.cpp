#include "ResultUI.h"
#include "Player.h"
#include "StageManager.h"
#include "Renderer.h"
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

void ResultUI::Draw(Renderer& renderer)
{
	if (!m_Player) return;
	if (!m_StageManager) return;
	if (m_Player->GetDeathTimer() > 0.0f) return;

	//背景
	renderer.DrawRect(m_Position, m_Scale, BLACK, true, Space::Screen);

	//文字（中央揃え）
	const Vector2 titlePos{ m_Position.x, m_Position.y + TITLE_OFFSET_Y };
	renderer.DrawLabel(titlePos, RED, "GAME OVER", TextAlign::Center, Space::Screen);
	renderer.DrawLabelFormat(Space::Screen, { titlePos.x, titlePos.y + LINE_SPACING }, RED, TextAlign::Center, "LEVEL : %d", m_StageManager->GetStageLoopCount());
}

void ResultUI::Destroy()
{
}
