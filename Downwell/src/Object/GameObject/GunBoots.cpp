#include "GunBoots.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "ObjectPool.h"
#include "GameHelper.h"
#include "AudioManager.h"

//‰¼
#include "DxLib.h"

void GunBoots::SetupBullet(GameObjectManager& manager)
{
	m_BulletPool.Setup(manager, BULLET_POOL_SIZE);
}

void GunBoots::Initialize()
{
	Object::Initialize();

	m_Ammo = MAX_AMMO;
}

void GunBoots::Finalize()
{
	Object::Finalize();
}

void GunBoots::Update(float dt)
{
}

void GunBoots::Draw()
{
}

void GunBoots::Destroy()
{
	Object::Destroy();
}

bool GunBoots::CreateBullet(const Vector2& position)
{
	if (m_Ammo <= 0)
	{
		AudioManager::GetInstance().PlaySE("ShotEmpty");
		return false;
	}

	Bullet* bullet = m_BulletPool.Get();
	if(bullet)
	{
		bullet->SetActive(true);
		bullet->Initialize();
		bullet->SetPosition(position);
		m_Ammo--;
		AudioManager::GetInstance().PlaySE("Shot");
		return true;
	}

	return false;
}

void GunBoots::Reload()
{
	if (m_Ammo >= MAX_AMMO) return;

	AudioManager::GetInstance().PlaySE("Reload");
	m_Ammo = MAX_AMMO;
}
