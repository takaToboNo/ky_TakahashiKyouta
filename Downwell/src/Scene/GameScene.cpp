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

	if (player)
	{
		if (floatingEnemy)
		{
			floatingEnemy->SetPlayer(player);
		}

		GunBoots* gunBoots = player->GetGunBoots();
		if (gunBoots)
		{
			gunBoots->SetOwner(player);
			gunBoots->SetupBullet(m_GameObjectManager);
		}
	}
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
