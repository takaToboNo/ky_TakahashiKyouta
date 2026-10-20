#pragma once
#include "Scene.h"
//StageManager‚ÉˆÚ‚·
#include "Map.h"

class Player;

class GameScene : public Scene
{
private:
	Player* m_Player = nullptr;
	//StageManager‚ÉˆÚ‚·
	Map m_Map;

public:
	GameScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
};
