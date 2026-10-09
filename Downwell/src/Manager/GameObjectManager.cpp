#include "GameObjectManager.h"
#include "GameObject.h"
#include <algorithm>

GameObjectManager::GameObjectManager() = default;
GameObjectManager::~GameObjectManager() = default;

void GameObjectManager::Finalize()
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Finalize();
	}
}

void GameObjectManager::Update(float dt)
{
	for (auto& gameObject : m_GameObjects)
	{
		gameObject->Update(dt);
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

	std::sort(m_GameObjects.begin(), m_GameObjects.end(),
		[](const std::unique_ptr<GameObject>& a, const std::unique_ptr<GameObject>& b)
		{ return a->GetLayer() < b->GetLayer(); });

	return ptr;
}
