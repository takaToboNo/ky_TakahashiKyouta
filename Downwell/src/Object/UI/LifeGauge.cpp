#include "LifeGauge.h"
#include "GameHelper.h"
#include "Player.h"
#include "Renderer.h"

void LifeGauge::Initialize()
{
	m_Scale = { GAUGE_WIDTH, GAUGE_HEIGHT };
	m_Color = RED;

	//m_Positionはゲージの左端・縦中央
	m_Position = { STAGE_LEFT - (m_Scale.x + OFFSET_FROM_STAGE), TOP_MARGIN + m_Scale.y * 0.5f };
}

void LifeGauge::Finalize()
{}

void LifeGauge::Update(float dt)
{}

void LifeGauge::Draw(Renderer& renderer)
{
	int maxHp = 0;
	int hp = 0;
	float propotionHp = 0.0f;
	if (m_Player)
	{
		maxHp = m_Player->GetMaxHp();
		hp = m_Player->GetHp();
		propotionHp = static_cast<float>(hp) / static_cast<float>(maxHp);
	}

	const Vector2 gaugeCenter{ m_Position.x + m_Scale.x * 0.5f, m_Position.y };

	//HPバー（左端を固定して、割合で幅を変える）
	const float barWidth = m_Scale.x * propotionHp;
	renderer.DrawRect({ m_Position.x + barWidth * 0.5f, m_Position.y }, { barWidth, m_Scale.y }, m_Color, true, Space::Screen);

	//枠上だけ余白を FRAME_PADDING 分増やす
	const float extraTop = static_cast<float>(FRAME_PADDING);
	renderer.DrawRectOutline({ gaugeCenter.x, gaugeCenter.y - extraTop * 0.5f }, { m_Scale.x, m_Scale.y + extraTop }, WHITE, FRAME_PADDING, Space::Screen);

	//HPの数値
	const float labelTop = m_Position.y - m_Scale.y * 0.5f + LABEL_OFFSET_Y;
	renderer.DrawLabelFormat(Space::Screen, { gaugeCenter.x, labelTop }, WHITE, TextAlign::Center, "%d/%d", hp, maxHp);
}

void LifeGauge::Destroy()
{}
