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
	m_Player = m_GameObjectManager.AddGameObject(std::make_unique<Player>());
	auto floatingEnemy = m_GameObjectManager.AddGameObject(std::make_unique<FloatingEnemy>());
	floatingEnemy->SetPosition({ 500.0f,300.0f });
	auto floatingEnemy1 = m_GameObjectManager.AddGameObject(std::make_unique<FloatingEnemy>());
	floatingEnemy1->SetPosition({ 700.0f,400.0f });
	auto floatingEnemy2 = m_GameObjectManager.AddGameObject(std::make_unique<FloatingEnemy>());
	floatingEnemy2->SetPosition({ 900.0f,600.0f });

	for (int i = 0; i < 100; i++)
	{//c‰¼’u‚«
		m_GameObjectManager.AddGameObject(std::make_unique<SolidBlock>())->SetPosition({ 400.0f, 0.0f + i * 47.0f });
		m_GameObjectManager.AddGameObject(std::make_unique<SolidBlock>())->SetPosition({ 400.0f + 47.0f * 10.0f, 0.0f + i * 47.0f });
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 9; j++)
		{//‰¡‰¼’u‚«
			if (j == 8) continue;
			m_GameObjectManager.AddGameObject(std::make_unique<BreakableBlock>())->SetPosition({ 447.0f + j * 47.0f, 800.0f + 2000.0f * i });
		}
	}

	for (int i = 0; i < 100; i++)
	{//c‰¼’u‚«
		m_GameObjectManager.AddGameObject(std::make_unique<SolidBlock>())->SetPosition({ 350.0f, 0.0f + i * 47.0f * 10.0f });
	}


	if (m_Player)
	{
		if (floatingEnemy)
		{
			floatingEnemy->SetPlayer(m_Player);
			floatingEnemy1->SetPlayer(m_Player);
			floatingEnemy2->SetPlayer(m_Player);
		}

		GunBoots* gunBoots = m_Player->GetGunBoots();
		if (gunBoots)
		{
			gunBoots->SetupBullet(m_GameObjectManager);
		}
	}

	m_Camera.SetTarget(m_Player);

	m_Camera.Initialize();
}

void GameScene::Finalize()
{
	m_GameObjectManager.Finalize();
	m_Camera.Finalize();

	Scene::Finalize();
}

void GameScene::Update(float dt)
{
	m_Camera.Update(dt);
	m_GameObjectManager.Update(dt);

	if (m_Player->GetDeathTimer() <= 0.0f)
	{
		m_RequestScene = SceneType::Result;
	}
}

void GameScene::Draw()
{
	m_GameObjectManager.Draw(m_Camera);
}
