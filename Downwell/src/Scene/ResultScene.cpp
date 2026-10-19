#define NOMINMAX
#include <algorithm>
#include "ResultScene.h"
#include "Input.h"
#include "GameHelper.h"

void ResultScene::Initialize()
{
	Scene::Initialize();

	m_Camera.Initialize();
}

void ResultScene::Finalize()
{
	m_GameObjectManager.Finalize();
	m_Camera.Finalize();

	Scene::Finalize();
}

void ResultScene::Update(float dt)
{
	m_Camera.Update(dt);
	m_GameObjectManager.Update(dt);

	if (Input::IsTrigger(Action::Decide))
	{
		m_RequestScene = SceneType::Title;
	}
}

void ResultScene::Draw()
{
	m_GameObjectManager.Draw(m_Camera);

	int x = static_cast<int>(WINDOW_WIDTH * 0.5f);
	int y = static_cast<int>(WINDOW_HEIGHT * 0.5f);
	DrawString(x, y, "Result", GetColor(RED.r, RED.g, RED.b));
}
