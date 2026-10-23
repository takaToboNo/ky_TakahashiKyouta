#pragma once
#include "Scene.h"
#include "StageManager.h"

#include "AmmoGauge.h"
#include "LifeGauge.h"
#include "StageCount.h"

class Player;

class GameScene : public Scene
{
private:
	Player* m_Player = nullptr;
	StageManager m_StageManager;

	//UI
	AmmoGauge m_AmmoGauge;
	LifeGauge m_LifeGauge;
	StageCount m_StageCount;

public:
	GameScene() = default;

	bool Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
};
