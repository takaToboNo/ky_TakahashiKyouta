#include "AmmoGauge.h"
#include "GameHelper.h"
#include "GunBoots.h"
#include "Renderer.h"

void AmmoGauge::Initialize()
{
	m_Scale = { CELL_WIDTH, CELL_HEIGHT };
	m_Color = WHITE;

	//m_Positionは一番下の弾セルの中心
	m_Position = { STAGE_RIGHT + OFFSET_FROM_STAGE, MAX_AMMO * m_Scale.y + TOP_MARGIN };
}

void AmmoGauge::Finalize()
{}

void AmmoGauge::Update(float dt)
{}

void AmmoGauge::Draw(Renderer& renderer)
{
	if (!m_GunBoots) return;

	const int   ammo = m_GunBoots->GetAmmo();
	const float cellPitch = m_Scale.y + CELL_GAP;   //セル1つ分の縦の間隔（高さ＋隙間）

	//弾セル（一番下から上へ積む）
	for (int i = 0; i < ammo; i++)
	{
		const Vector2 cellCenter{ m_Position.x, m_Position.y - i * cellPitch };
		renderer.DrawRect(cellCenter, m_Scale, m_Color, true, Space::Screen);
	}

	//枠（最大弾数分の領域を囲む）
	const float   gaugeBottom = m_Position.y + m_Scale.y * 0.5f;
	const float   gaugeHeight = MAX_AMMO * cellPitch;
	const Vector2 frameCenter{ m_Position.x, gaugeBottom - gaugeHeight * 0.5f };
	renderer.DrawRectOutline(frameCenter, { m_Scale.x, gaugeHeight }, RED, FRAME_PADDING, Space::Screen);

	//残弾数（ゲージの下に中央揃え）
	const Vector2 labelPos{ m_Position.x, gaugeBottom + LABEL_OFFSET_Y };
	renderer.DrawLabelFormat(Space::Screen, labelPos, WHITE, TextAlign::Center, "%d", ammo);
}

void AmmoGauge::Destroy()
{}
