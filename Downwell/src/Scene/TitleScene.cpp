#include "TitleScene.h"
#include "DxLib.h"
#include "GameHelper.h"

void TitleScene::Initialize()
{
	Scene::Initialize();
}

void TitleScene::Finalize()
{
	Scene::Finalize();
}

void TitleScene::Update()
{
	m_KeyInterval--;
	m_KeyInterval = max(m_KeyInterval, 0);
	if (CheckHitKey(KEY_INPUT_RETURN) && m_KeyInterval == 0)
	{
		m_RequestScene = SceneType::Game;
	}
}

void TitleScene::Draw()
{
	DrawBox(0.0f, 0.0f, kScreenWidth, kScreenHeight, GetColor(30,0,0), TRUE);
}
