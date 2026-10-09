#include "GameObjectManager.h"

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
