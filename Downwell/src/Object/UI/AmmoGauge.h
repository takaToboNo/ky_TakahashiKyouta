#pragma once
#include "UI.h"

class GunBoots;

class AmmoGauge : public UI
{
private:
	static constexpr float CELL_WIDTH = 30.0f;			//弾セル1つの幅
	static constexpr float CELL_HEIGHT = 40.0f;			//弾セル1つの高さ
	static constexpr float CELL_GAP = 1.0f;				//弾セル同士の隙間

	static constexpr float OFFSET_FROM_STAGE = 100.0f;	//ステージ右端からの距離
	static constexpr float TOP_MARGIN = 100.0f;			//画面上端からの余白

	static constexpr int   FRAME_PADDING = 3;			//枠をセルより大きく描くための余白
	static constexpr float LABEL_OFFSET_Y = 10.0f;		//ゲージ下端から数字までの距離

	GunBoots* m_GunBoots = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void Destroy() override;

	void SetGunBoots(GunBoots* gunBoots) { m_GunBoots = gunBoots; }

};