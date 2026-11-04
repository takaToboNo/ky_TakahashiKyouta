#include "GameManager.h"
#include "GameHelper.h"
#include "Input.h"
#include "AudioManager.h"
#include "DxLib.h"

bool GameManager::Initialize()
{
	int result;
	result = ChangeWindowMode(TRUE);
	if (result != 0) return false;
	result = SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	if (result != 0) return false;

	SetAlwaysRunFlag(TRUE);
	
	result = DxLib_Init();
	if (result != 0) return false;
	result = SetDrawScreen(DX_SCREEN_BACK);
	if (result != 0) return false;

	if (!m_Renderer.Initialize()) return false;

	AudioManager::GetInstance().Initialize();

	m_ImGuiManager.Initialize();
	m_Timer.Initialize();
	result = m_SceneManager.Initialize();
	if (result == 0) return false;

	return true;
}

void GameManager::Finalize()
{
	AudioManager::GetInstance().Finalize();

	m_SceneManager.Finalize();
	m_Timer.Finalize();
	m_ImGuiManager.Finalize();
	m_Renderer.Finalize();

	DxLib_End();
}

int GameManager::Run()
{
	if (!Initialize()) return -1;

	while (ProcessMessage() == 0 && !Input::IsTrigger(Action::End))
	{
		m_Timer.Tick();

		int count = 0;

		while (count < MAX_UPDATE && m_Timer.ConsumeFixedStep())
		{
			Input::Update();
			m_Timer.Update();
			m_SceneManager.Update(m_Timer.GetFixedDeltaTime());

			count++;
		}

		if (count >= MAX_UPDATE && m_Timer.HasRemainingStep())
		{
			//追いつけなかった分を捨てる
 			m_Timer.DiscardRemainingSteps();
		}

		m_ImGuiManager.BeginFrame();

		bool result;
		result = m_Renderer.BeginFrame();
		if (!result) return -1;

		m_Timer.Draw();
		m_SceneManager.Draw(m_Renderer);

		m_ImGuiManager.EndFrame();

		result = m_Renderer.EndFrame();
		if (!result) return -1;
	}

	Finalize();

	return 0;
}
