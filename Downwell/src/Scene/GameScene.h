#pragma once
#include "Scene.h"

class Player;

class GameScene : public Scene
{
private:
	Player* m_Player = nullptr;

public:
	GameScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
};
