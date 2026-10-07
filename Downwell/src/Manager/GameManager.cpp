#include "GameManager.h"
#include "GameHelper.h"
#include "DxLib.h"
#include <cassert>

void GameManager::Initialize()
{
	SetGraphMode(kScreenWidth, kScreenHeight, 32);
	assert(DxLib_Init() == 0);
	assert(SetDrawScreen(DX_SCREEN_BACK) == 0);

	m_SceneManager.Initialize();
}

void GameManager::Finalize()
{
	m_SceneManager.Finalize();

	DxLib_End();
}

void GameManager::Run()
{
	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		assert(ClearDrawScreen() == 0);
		m_SceneManager.Update();
		m_SceneManager.Draw();
		assert(ScreenFlip() == 0);
	}
}
