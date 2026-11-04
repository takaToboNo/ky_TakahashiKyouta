#include "TitleScene.h"
#include "Input.h"
#include "GameHelper.h"
#include "AudioManager.h"
#include "Renderer.h"

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

void TitleScene::Draw(Renderer& renderer)
{
	renderer.SetCamera(&m_Camera);

	m_GameObjectManager.Draw(renderer);
	m_GameObjectManager.DrawDebug();

	const Vector2 screenCenter{ WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f };
	renderer.DrawLabel(screenCenter, RED, "Downwell", TextAlign::Center, Space::Screen);
}
