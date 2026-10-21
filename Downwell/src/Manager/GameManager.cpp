#include "GameManager.h"
#include "GameHelper.h"
#include "Input.h"

bool GameManager::Initialize()
{
	int result;
	result = ChangeWindowMode(TRUE);
	if (result != 0) return false;
	result = SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	if (result != 0) return false;
	
	result = DxLib_Init();
	if (result != 0) return false;
	result = SetDrawScreen(DX_SCREEN_BACK);
	if (result != 0) return false;

	m_Timer.Initialize();
	m_SceneManager.Initialize();

	return true;
}

void GameManager::Finalize()
{
	m_SceneManager.Finalize();
	m_Timer.Finalize();

	DxLib_End();
}

int GameManager::Run()
{
	if (!Initialize()) return -1;

	while (ProcessMessage() == 0 && !Input::IsTrigger(Action::End))
	{
		m_Timer.Tick();

		int count = 0;

		while (m_Timer.ConsumeFixedStep() && count < 3)
		{
			Input::Update();
			m_Timer.Update();
			m_SceneManager.Update(m_Timer.GetFixedDeltaTime());

			count++;
		}

		int result;
		result = ClearDrawScreen();
		if (result != 0) return -1;
		m_Timer.Draw();
		m_SceneManager.Draw();
		result = ScreenFlip();
		if (result != 0) return -1;
	}

	Finalize();

	return 0;
}
