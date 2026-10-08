#define NOMINMAX
#include <algorithm>
#include "ResultScene.h"
#include "DxLib.h"
#include "GameHelper.h"

void ResultScene::Initialize()
{
	Scene::Initialize();
}

void ResultScene::Finalize()
{
	m_GameObjectManager.Finalize();

	Scene::Finalize();
}

void ResultScene::Update()
{
	m_GameObjectManager.Update();

	m_KeyInterval--;
	m_KeyInterval = std::max(m_KeyInterval, 0);
	if (CheckHitKey(KEY_INPUT_RETURN) && m_KeyInterval == 0)
	{
		m_RequestScene = SceneType::Title;
	}
}

void ResultScene::Draw()
{
	m_GameObjectManager.Draw();

	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 30, 0), TRUE);
}
