#define NOMINMAX
#include <algorithm>
#include <memory>
#include "GameScene.h"
#include "DxLib.h"

#include "Player.h"
#include "WalkerEnemy.h"
#include "FloatingEnemy.h"

void GameScene::Initialize()
{
	Scene::Initialize();

	m_GameObjectManager.AddGameObject(std::make_unique<Player>());
	m_GameObjectManager.AddGameObject(std::make_unique<WalkerEnemy>());
	m_GameObjectManager.AddGameObject(std::make_unique<FloatingEnemy>());
}

void GameScene::Finalize()
{
	m_ObjectManager.Finalize();
	m_GameObjectManager.Finalize();

	Scene::Finalize();
}

void GameScene::Update(float dt)
{
	m_ObjectManager.Update(dt);
	m_GameObjectManager.Update(dt);

	m_KeyInterval--;
	m_KeyInterval = std::max(m_KeyInterval, 0);
	if (CheckHitKey(KEY_INPUT_RETURN) && m_KeyInterval == 0)
	{
		m_RequestScene = SceneType::Result;
	}
}

void GameScene::Draw()
{
	m_ObjectManager.Draw();
	m_GameObjectManager.Draw();
}
