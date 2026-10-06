#include "SceneManager.h"

//‰¼
#include "Main.h"
#include "Player.h"

void SceneManager::Initialize()
{
	SetGraphMode(1280, 720, 32);
	assert(DxLib_Init() == 0);
	assert(SetDrawScreen(DX_SCREEN_BACK) == 0);

	

	m_pPlayer = new Player();//‰¼
	m_pPlayer->Initialize();//‰¼
}

void SceneManager::Finalize()
{
	m_pPlayer->Finalize();//‰¼

	DxLib_End();
}

void SceneManager::Update()
{
	m_pPlayer->Update();//‰¼
}

void SceneManager::Draw()
{
	m_pPlayer->Draw();//‰¼
}
