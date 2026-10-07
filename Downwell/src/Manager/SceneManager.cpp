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

void SceneManager::Update()
{
	m_Scene->Update();

	ChangeScene();
}

void SceneManager::Draw()
{
	m_Scene->Draw();
}

void SceneManager::ChangeScene()
{
	if (m_Scene->GetSceneRequest() == SceneType::None) return;

	if (m_Scene) m_Scene->Finalize();

	switch (m_Scene->GetSceneRequest())
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
		break;
	}

	if (m_Scene) m_Scene->Initialize();
}
