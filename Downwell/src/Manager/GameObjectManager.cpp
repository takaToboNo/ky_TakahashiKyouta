#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::GameObjectManager() = default;
GameObjectManager::~GameObjectManager() = default;

void GameObjectManager::Finalize()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Finalize();
	}
}

void GameObjectManager::Update()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update();
	}
}

void GameObjectManager::Draw()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Draw();
	}
}

GameObject* GameObjectManager::AddGameObject(std::unique_ptr<GameObject> gameObject)
{
	GameObject* ptr = gameObject.get();

	m_GameObjects.push_back(std::move(gameObject));
	m_GameObjects.back()->Initialize();

	return ptr;
}
