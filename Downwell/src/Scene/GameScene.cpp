#define NOMINMAX
#include <algorithm>
#include <memory>
#include "GameScene.h"
#include "Input.h"

#include "Player.h"
#include "WalkerEnemy.h"
#include "FloatingEnemy.h"
#include "BreakableBlock.h"
#include "SolidBlock.h"

void GameScene::Initialize()
{
	Scene::Initialize();

	m_GameObjectManager.AddGameObject(std::make_unique<WalkerEnemy>());

	//‰¼’u‚«
	auto player = m_GameObjectManager.AddGameObject(std::make_unique<Player>());
	auto floatingEnemy = m_GameObjectManager.AddGameObject(std::make_unique<FloatingEnemy>());

	for (int i = 0; i < 20; i++)
	{//c‰¼’u‚«
		m_GameObjectManager.AddGameObject(std::make_unique<SolidBlock>())->SetPosition({ 150.0f, 150.0f + i * 30.0f });
		m_GameObjectManager.AddGameObject(std::make_unique<BreakableBlock>())->SetPosition({ 1200.0f, 150.0f + i * 30.0f });
	}
	for (int i = 0; i < 5; i++)
	{//‰¡‰¼’u‚«
		m_GameObjectManager.AddGameObject(std::make_unique<SolidBlock>())->SetPosition({ 180.0f + i * 30.0f, 700.0f });
		m_GameObjectManager.AddGameObject(std::make_unique<BreakableBlock>())->SetPosition({ 1170.0f - i * 30.0f, 700.0f });
		m_GameObjectManager.AddGameObject(std::make_unique<BreakableBlock>())->SetPosition({ 1170.0f - i * 30.0f, 500.0f });
	}

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
