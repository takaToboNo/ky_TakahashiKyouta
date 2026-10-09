#include "SceneManager.h"

void SceneManager::Initialize()
{
	m_Scene = std::make_unique<GameScene>();
	m_Scene->Initialize();
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

	case SceneType::Result:
		m_Scene = std::make_unique<ResultScene>();
		break;

	default:
		return;
	}
	m_Scene->Initialize();
}
