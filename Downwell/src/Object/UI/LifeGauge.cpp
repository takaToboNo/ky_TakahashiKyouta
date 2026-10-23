#include "LifeGauge.h"
#include "GameHelper.h"
#include "Player.h"
#include "DxLib.h"

void LifeGauge::Initialize()
{
	m_Scale = { 230.0f,20.0f };
	m_Color = RED;

	m_Position = { STAGE_LEFT - (m_Scale.x + 100.0f), m_Scale.y + 30.0f };
}

void LifeGauge::Finalize()
{
}

void LifeGauge::Update(float dt)
{
}

void LifeGauge::Draw()
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

	{//HPÉoÅ[ï`âÊ
		int x1, y1;
		x1 = static_cast<int>(m_Position.x);
		y1 = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f));
		int x2, y2;
		x2 = static_cast<int>(m_Position.x + (m_Scale.x * propotionHp));
		y2 = static_cast<int>(m_Position.y + (m_Scale.y * 0.5f));
		DrawBox(x1, y1, x2, y2, GetColor(m_Color.r, m_Color.g, m_Color.b), TRUE);

		const int HP_GAUGE_MARGIN = 3;	//ògï`âÊÇè≠ÇµëÂÇ´ÇﬂÇ…Ç∑ÇÈÇΩÇﬂÇÃíl
		x1 -= HP_GAUGE_MARGIN;
		y1 -= HP_GAUGE_MARGIN * 2;	//è„ÇæÇØè≠Çµó]îíëÂÇ´ÇﬂÇ…Ç∑ÇÈ
		x2 = static_cast<int>(m_Position.x + m_Scale.x) + HP_GAUGE_MARGIN;
		y2 += HP_GAUGE_MARGIN;
		DrawBox(x1, y1, x2, y2, GetColor(WHITE.r, WHITE.g, WHITE.b), FALSE);
	}

	//ílï`âÊ
	int x = static_cast<int>(m_Position.x + (m_Scale.x * 0.5f)) - 10;
	int y = static_cast<int>(m_Position.y - (m_Scale.y * 0.5f)) + 2;
	DrawFormatString(x, y, GetColor(WHITE.r, WHITE.g, WHITE.b), "%d/%d", hp, maxHp);
}

void LifeGauge::Destroy()
{
}
