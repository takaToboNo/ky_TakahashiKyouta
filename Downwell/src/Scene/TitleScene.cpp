#define NOMINMAX
#include <algorithm>
#include "TitleScene.h"
#include "Input.h"
#include "GameHelper.h"
#include "AudioManager.h"

bool TitleScene::Initialize()
{
	bool result = true;
	result = Scene::Initialize();
	if (!result) return false;

	m_Camera.Initialize();

	m_GameObjectManager.SetCamera(&m_Camera);

	return true;
}

void TitleScene::Finalize()
{
	m_Camera.Finalize();
	m_GameObjectManager.Finalize();

	Scene::Finalize();
}

void TitleScene::Update(float dt)
{
	m_Camera.Update(dt);
	m_GameObjectManager.Update(dt);

	if (Input::IsTrigger(Action::Action))
	{
		AudioManager::GetInstance().PlaySE("Decide");
		m_RequestScene = SceneType::Game;
	}
}

void TitleScene::Draw()
{
	m_GameObjectManager.Draw();
	m_GameObjectManager.DrawDebug();

	int x = static_cast<int>(WINDOW_WIDTH * 0.5f);
	int y = static_cast<int>(WINDOW_HEIGHT * 0.5f);
	DrawString(x, y, "Downwell", GetColor(RED.r, RED.g, RED.b));
}
