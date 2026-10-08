#include "GameManager.h"
#include "GameHelper.h"
#include "DxLib.h"

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

	m_SceneManager.Initialize();

	return true;
}

void GameManager::Finalize()
{
	m_SceneManager.Finalize();

	DxLib_End();
}

int GameManager::Run()
{
	if (!Initialize()) return -1;

	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		int result;
		result = ClearDrawScreen();
		if (result != 0) return -1;
		m_SceneManager.Update();
		m_SceneManager.Draw();
		result = ScreenFlip();
		if (result != 0) return -1;
	}

	Finalize();

	return 0;
}
