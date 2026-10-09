#define NOMINMAX
#include <algorithm>
#include "TitleScene.h"
#include "DxLib.h"
#include "GameHelper.h"

void TitleScene::Initialize()
{
	Scene::Initialize();
}

void TitleScene::Finalize()
{
	m_ObjectManager.Finalize();
	m_GameObjectManager.Finalize();

	Scene::Finalize();
}

void TitleScene::Update(float dt)
{
	m_ObjectManager.Update(dt);
	m_GameObjectManager.Update(dt);

	m_KeyInterval--;
	m_KeyInterval = std::max(m_KeyInterval, 0);
	if (CheckHitKey(KEY_INPUT_RETURN) && m_KeyInterval == 0)
	{
		m_RequestScene = SceneType::Game;
	}
}

void TitleScene::Draw()
{
	m_ObjectManager.Draw();
	m_GameObjectManager.Draw();

	int x = static_cast<int>(WINDOW_WIDTH * 0.5f);
	int y = static_cast<int>(WINDOW_HEIGHT * 0.5f);
	DrawString(x, y, "Title", GetColor(GREEN.r, GREEN.g, GREEN.b));
}
