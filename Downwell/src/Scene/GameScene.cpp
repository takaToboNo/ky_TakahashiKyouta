#define NOMINMAX
#include <algorithm>
#include <memory>
#include "GameScene.h"
#include "Input.h"

#include "Player.h"
#include "WalkerEnemy.h"
#include "FloatingEnemy.h"

void GameScene::Initialize()
{
	Scene::Initialize();

	m_GameObjectManager.AddGameObject(std::make_unique<WalkerEnemy>());
	
	auto player = m_GameObjectManager.AddGameObject(std::make_unique<Player>());
	auto floatingEnemy = m_GameObjectManager.AddGameObject(std::make_unique<FloatingEnemy>());
	floatingEnemy->SetPlayer(player);
}

void GameScene::Finalize()
{
	m_GameObjectManager.Finalize();

	Scene::Finalize();
}

void GameScene::Update(float dt)
{
	m_GameObjectManager.Update(dt);

	if (Input::IsTrigger(Action::Decide))
	{
		m_RequestScene = SceneType::Result;
	}
}

void GameScene::Draw()
{
	m_GameObjectManager.Draw();
}
