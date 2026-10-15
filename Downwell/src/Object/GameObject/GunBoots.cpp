#include "GunBoots.h"
#include "GameObjectManager.h"
#include "Player.h"

//仮
#include "DxLib.h"

void GunBoots::SetupBullet(GameObjectManager& manager)
{
	//中身を空にする
	m_BulletPool.clear();
	//要素数を先に確保
	m_BulletPool.reserve(MAX_POOL_SIZE);

	for (int i = 0; i < MAX_POOL_SIZE; i++)
	{
		Bullet* bullet = manager.AddGameObject(std::make_unique<Bullet>());

		if (!bullet)
		{
			continue;
		}

		//プール状態にしておく
		bullet->SetActive(false);
		m_BulletPool.push_back(bullet);
	}
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
	DrawFormatString(350, 10, GetColor(WHITE.r, WHITE.g, WHITE.b), "BulletPool : %d/%d", static_cast<int>(m_BulletPool.size()), MAX_POOL_SIZE);
	DrawFormatString(350, 30, GetColor(WHITE.r, WHITE.g, WHITE.b), "Ammo : %d/%d", m_Ammo, MAX_AMMO);
#endif
}

void GunBoots::Destroy()
{
	Object::Destroy();
}

bool GunBoots::CreateBullet(const Vector2& position)
{
	if (m_Ammo <= 0) return false;

	for (auto bullet : m_BulletPool)
	{
		if (!bullet) continue;
		
		if (bullet->IsActive()) continue;
		
		Vector2 offset = Vector2::Zero();
		if (m_Owner)
		{
			offset.y += m_Owner->GetScale().y * 0.5f;
		}

		bullet->SetActive(true);
		bullet->Initialize();
		bullet->SetPosition(position + offset);
		m_Ammo--;
		return true;
	}

	return false;
}
