#include "GunBoots.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "ObjectPool.h"
#include "GameHelper.h"

//仮
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
#ifdef _DEBUG
	//デバッグ表示
	DrawFormatString(350, 10, GetColor(GRAY.r, GRAY.g, GRAY.b), "Ammo : %d/%d", m_Ammo, MAX_AMMO);
#endif
}

void GunBoots::Destroy()
{
	Object::Destroy();
}

bool GunBoots::CreateBullet(const Vector2& position)
{
	if (m_Ammo <= 0) return false;

	Bullet* bullet = m_BulletPool.Get();
	if(bullet)
	{
		bullet->SetActive(true);
		bullet->Initialize();
		bullet->SetPosition(position);
		m_Ammo--;
		return true;
	}

	return false;
}
