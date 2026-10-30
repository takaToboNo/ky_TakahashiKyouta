#include "SceneManager.h"

bool SceneManager::Initialize()
{
	bool result = true;

	m_Scene = std::make_unique<TitleScene>();

	result = m_Scene->Initialize();
	if (!result) return false;

	return true;
}

void SceneManager::Finalize()
{
	m_Scene->Finalize();
}

void SceneManager::Update(float dt)
{
	m_Scene->Update(dt);

	ChangeScene();
}

void SceneManager::Draw()
{
	m_Scene->Draw();
}

void SceneManager::ChangeScene()
{
	if (!m_Scene) return;

	if (m_Scene->GetSceneRequest() == SceneType::None) return;
	SceneType sceneType = m_Scene->GetSceneRequest();

	m_Scene->Finalize();
	switch (sceneType)
	{
	case SceneType::Title:
		m_Scene = std::make_unique<TitleScene>();
		break;

	case SceneType::Game:
		m_Scene = std::make_unique<GameScene>();
		break;

	default:
		return;
	}
	m_Scene->Initialize();
}
