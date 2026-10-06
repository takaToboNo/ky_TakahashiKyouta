#include "SceneManager.h"

#include "Main.h"//‰¼

void SceneManager::Initialize()
{
	SetGraphMode(1280, 720, 32);
	assert(DxLib_Init() == 0);
	assert(SetDrawScreen(DX_SCREEN_BACK) == 0);

	m_pPlayer->Initialize();//‰¼
	m_pGunBoots->Initialize();//‰¼
	m_pWalkerEnemy->Initialize();//‰¼
	m_pFloatingEnemy->Initialize();//‰¼
}

void SceneManager::Finalize()
{
	m_pFloatingEnemy->Finalize();//‰¼
	m_pWalkerEnemy->Finalize();//‰¼
	m_pGunBoots->Finalize();//‰¼
	m_pPlayer->Finalize();//‰¼

	DxLib_End();
}

void SceneManager::Update()
{
	m_pPlayer->Update();//‰¼
	m_pGunBoots->Update();//‰¼
	m_pWalkerEnemy->Update();//‰¼
	m_pFloatingEnemy->Update();//‰¼
}

void SceneManager::Draw()
{
	m_pPlayer->Draw();//‰¼
	m_pGunBoots->Draw();//‰¼
	m_pWalkerEnemy->Draw();//‰¼
	m_pFloatingEnemy->Draw();//‰¼
}
