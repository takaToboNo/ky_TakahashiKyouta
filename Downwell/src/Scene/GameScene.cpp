#include "GameScene.h"

void GameScene::Initialize()
{
	if (m_pPlayer) m_pPlayer->Initialize();//‰¼
	if (m_pGunBoots) m_pGunBoots->Initialize();//‰¼
	if (m_pWalkerEnemy) m_pWalkerEnemy->Initialize();//‰¼
	if (m_pFloatingEnemy) m_pFloatingEnemy->Initialize();//‰¼
}

void GameScene::Finalize()
{
	if (m_pFloatingEnemy) m_pFloatingEnemy->Finalize();//‰¼
	if (m_pWalkerEnemy) m_pWalkerEnemy->Finalize();//‰¼
	if (m_pGunBoots) m_pGunBoots->Finalize();//‰¼
	if (m_pPlayer) m_pPlayer->Finalize();//‰¼
}

void GameScene::Update()
{
	if (m_pPlayer) m_pPlayer->Update();//‰¼
	if (m_pGunBoots) m_pGunBoots->Update();//‰¼
	if (m_pWalkerEnemy) m_pWalkerEnemy->Update();//‰¼
	if (m_pFloatingEnemy) m_pFloatingEnemy->Update();//‰¼
}

void GameScene::Draw()
{
	if (m_pPlayer) m_pPlayer->Draw();//‰¼
	if (m_pGunBoots) m_pGunBoots->Draw();//‰¼
	if (m_pWalkerEnemy) m_pWalkerEnemy->Draw();//‰¼
	if (m_pFloatingEnemy) m_pFloatingEnemy->Draw();//‰¼
}
