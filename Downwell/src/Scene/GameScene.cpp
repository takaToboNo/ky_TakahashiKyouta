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
#include "GameHelper.h"

void GameScene::Initialize()
{
	Scene::Initialize();

	//‰¼’u‚«
	m_Player = m_GameObjectManager.AddGameObject(std::make_unique<Player>());

	m_StageManager.Initialize();
	m_StageManager.GenerateStage(m_GameObjectManager, { STAGE_LEFT, 0.0f }, m_Player);

	if (m_Player)
	{
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
	m_StageManager.Finalize();

	Scene::Finalize();
}

void GameScene::Update(float dt)
{
	m_StageManager.Update(m_Player->GetPosition().y);
	m_Camera.Update(dt);
	m_GameObjectManager.Update(dt);

	if (m_Player->GetDeathTimer() <= 0.0f || m_StageManager.GetCurrentSection() == -1)
	{
		m_RequestScene = SceneType::Result;
	}
}

void GameScene::Draw()
{
	m_StageManager.Draw();
	m_GameObjectManager.Draw(m_Camera);
}
