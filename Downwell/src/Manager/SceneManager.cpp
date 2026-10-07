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
}

void SceneManager::Draw()
{
	m_Scene->Draw();
}

void SceneManager::RequestScene(std::unique_ptr<Scene> next)
{
	m_NextScene = std::move(next);
}

void SceneManager::SetScene()
{
	if (m_Scene == m_NextScene) return;

	if (m_Scene) m_Scene->Finalize();
	m_Scene = std::move(m_NextScene);
	if (m_Scene) m_Scene->Initialize();
}
