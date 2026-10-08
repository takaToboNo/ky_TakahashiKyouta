#pragma once
#include "Scene.h"

class GameScene : public Scene
{
private:

public:
	GameScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};
