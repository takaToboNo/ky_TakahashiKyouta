#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
private:

public:
	TitleScene() = default;

	bool Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
};
