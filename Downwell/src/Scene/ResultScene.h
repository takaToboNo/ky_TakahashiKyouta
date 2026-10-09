#pragma once
#include "Scene.h"

class ResultScene : public Scene
{
private:

public:
	ResultScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
};
