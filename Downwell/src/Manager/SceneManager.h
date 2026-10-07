#pragma once
#include <memory>
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"

class SceneManager
{
private:
	std::unique_ptr<Scene> m_Scene = std::make_unique<TitleScene>();
	std::unique_ptr<Scene> m_NextScene = std::make_unique<TitleScene>();

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void RequestScene(std::unique_ptr<Scene> next);
	void SetScene();
};
