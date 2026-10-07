#include "SceneManager.h"

void SceneManager::Initialize()
{
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
