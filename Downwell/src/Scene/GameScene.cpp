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

	m_Player = m_GameObjectManager.AddGameObject(std::make_unique<Player>());

	bool result = true;
	result = m_StageManager.Initialize();
	if (!result)
	{
		MessageBoxA(NULL, ".csv‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½", "Fatal Error", MB_OK | MB_ICONERROR);
		DxLib_End();
	}
	m_StageManager.GenerateStage(m_GameObjectManager, { STAGE_LEFT, 0.0f }, m_Player);

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
