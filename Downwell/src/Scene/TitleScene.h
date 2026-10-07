#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
private:

public:
	TitleScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};
