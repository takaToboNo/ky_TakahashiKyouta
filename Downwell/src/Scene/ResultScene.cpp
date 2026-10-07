#include "ResultScene.h"
#include "DxLib.h"
#include "GameHelper.h"

void ResultScene::Initialize()
{
	Scene::Initialize();
}

void ResultScene::Finalize()
{
	Scene::Finalize();
}

void ResultScene::Update()
{
	m_KeyInterval--;
	m_KeyInterval = max(m_KeyInterval, 0);
	if (CheckHitKey(KEY_INPUT_RETURN) && m_KeyInterval == 0)
	{
		m_RequestScene = SceneType::Title;
	}
}

void ResultScene::Draw()
{
	DrawBox(0.0f, 0.0f, kScreenWidth, kScreenHeight, GetColor(0, 30, 0), TRUE);
}
