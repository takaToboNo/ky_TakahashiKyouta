#pragma once
#include "Scene.h"
#include "StageManager.h"

class Player;

class GameScene : public Scene
{
private:
	Player* m_Player = nullptr;
	StageManager m_StageManager;

public:
	GameScene() = default;

	bool Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
};
