#pragma once
#include "Scene.h"

class ResultScene : public Scene
{
private:

public:
	ResultScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};
