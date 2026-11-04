#pragma once
#include "UI.h"

class Player;

class LifeGauge : public UI
{
private:
	static constexpr float GAUGE_WIDTH = 230.0f;		//ゲージの幅
	static constexpr float GAUGE_HEIGHT = 20.0f;		//ゲージの高さ

	static constexpr float OFFSET_FROM_STAGE = 100.0f;	//ゲージ右端からステージ左端までの距離
	static constexpr float TOP_MARGIN = 40.0f;			//画面上端からゲージ上端までの距離

	static constexpr int   FRAME_PADDING = 3;			//枠をバーより大きく描くための余白
	static constexpr float FRAME_EXTRA_TOP = 3.0f;		//枠の上側だけに追加する余白（数値の文字を収めるため）
	static constexpr float LABEL_OFFSET_Y = 2.0f;		//バー上端から文字までの距離

	Player* m_Player = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void Destroy() override;

	void SetPlayer(Player* player) { m_Player = player; }

};