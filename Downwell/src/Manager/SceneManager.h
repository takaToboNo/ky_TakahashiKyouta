#pragma once
#include <memory>
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> m_Scene = std::make_unique<TitleScene>();

public:
	SceneManager() = default;
	~SceneManager() = default;

	bool Initialize();
	void Finalize();
	void Update(float dt);
	void Draw();

	void ChangeScene();
};
