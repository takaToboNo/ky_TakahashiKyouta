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
	m_Map.LoadMapData("Start.csv");
	m_Map.SetMap(m_GameObjectManager, Vector2(STAGE_LEFT,0.0f), m_Player);
	m_Map.LoadMapData("Chunk01.csv");
	m_Map.SetMap(m_GameObjectManager, Vector2(STAGE_LEFT,TILE_SIZE * static_cast<float>(MAP_SIZE_Y) * 1.0f), m_Player);
	m_Map.LoadMapData("Chunk02.csv");
	m_Map.SetMap(m_GameObjectManager, Vector2(STAGE_LEFT,TILE_SIZE * static_cast<float>(MAP_SIZE_Y) * 2.0f), m_Player);

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
