#include "SceneManager.h"

#include "Main.h"//‰¼

void SceneManager::Initialize()
{
	SetGraphMode(1280, 720, 32);
	assert(DxLib_Init() == 0);
	assert(SetDrawScreen(DX_SCREEN_BACK) == 0);

	m_pPlayer->Initialize();//‰¼
	m_pGunBoots->Initialize();//‰¼
	m_pBullet->Initialize();//‰¼
}

void SceneManager::Finalize()
{
	m_pBullet->Finalize();//‰¼
	m_pGunBoots->Finalize();//‰¼
	m_pPlayer->Finalize();//‰¼

	DxLib_End();
}

void SceneManager::Update()
{
	m_pPlayer->Update();//‰¼
	m_pGunBoots->Update();//‰¼
	m_pBullet->Update();//‰¼
}

void SceneManager::Draw()
{
	m_pPlayer->Draw();//‰¼
	m_pGunBoots->Draw();//‰¼
	m_pBullet->Draw();//‰¼
}
