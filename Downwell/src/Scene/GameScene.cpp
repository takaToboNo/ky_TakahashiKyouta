#define NOMINMAX
#include <algorithm>
#include <memory>
#include "GameScene.h"
#include "Input.h"
#include "AudioManager.h"

#include "Player.h"
#include "WalkerEnemy.h"
#include "FloatingEnemy.h"
#include "BreakableBlock.h"
#include "SolidBlock.h"
#include "GameHelper.h"

bool GameScene::Initialize()
{
	bool result = true;
	result = Scene::Initialize();
	if (!result) return false;

	m_Player = m_GameObjectManager.AddGameObject(std::make_unique<Player>());

	result = m_StageManager.Initialize(m_GameObjectManager);
	if (!result) return false;
	m_StageManager.SetCamera(&m_Camera);

	m_Camera.SetTarget(m_Player);
	m_Camera.Initialize();

	m_GameObjectManager.SetCamera(&m_Camera);
	m_GameObjectManager.SortGameObjectsByLayer();

	//UI
	m_AmmoGauge.Initialize();
	m_AmmoGauge.SetGunBoots(m_Player->GetGunBoots());
	m_LifeGauge.Initialize();
	m_LifeGauge.SetPlayer(m_Player);
	m_StageCount.Initialize();
	m_StageCount.SetStageManager(&m_StageManager);
	m_ResultUI.Initialize();
	m_ResultUI.SetPlayer(m_Player);
	m_ResultUI.SetStageManager(&m_StageManager);

	return true;
}

void GameScene::Finalize()
{
	//UI
	m_ResultUI.Finalize();
	m_StageCount.Finalize();
	m_LifeGauge.Finalize();
	m_AmmoGauge.Finalize();

	m_GameObjectManager.Finalize();
	m_Camera.Finalize();
	m_StageManager.Finalize();

	Scene::Finalize();
}

void GameScene::Update(float dt)
{
	m_Camera.Update(dt);
	m_GameObjectManager.Update(dt);
	m_StageManager.Update(m_GameObjectManager, m_Player);

	//UI
	m_AmmoGauge.Update(dt);
	m_LifeGauge.Update(dt);
	m_StageCount.Update(dt);
	m_ResultUI.Update(dt);

	if (m_Player->GetDeathTimer() <= 0.0f)
	{
		if (Input::IsTrigger(Action::Action))
		{
			AudioManager::GetInstance().PlaySE("Decide");
			m_RequestScene = SceneType::Title;
		}
	}
}

void GameScene::Draw()
{
	m_GameObjectManager.Draw();
	m_StageManager.Draw();

	//UI
	m_AmmoGauge.Draw();
	m_LifeGauge.Draw();
	m_StageCount.Draw();
	m_ResultUI.Draw();
}
