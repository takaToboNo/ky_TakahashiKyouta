#include "GunBoots.h"

//仮
#include "DxLib.h"

void GunBoots::Initialize()
{
	Object::Initialize();

	m_Ammo = MAX_AMMO;

	m_BulletPool.clear();
	m_BulletPool.reserve(MAX_POOL_SIZE);
	for (int i = 0; i < MAX_POOL_SIZE; i++)
	{
		m_BulletPool.push_back(std::make_unique<Bullet>());
	}
}

void GunBoots::Finalize()
{
	for (auto& bullet : m_pBullets)
	{
		bullet->Finalize();
	}

	Object::Finalize();
}

void GunBoots::Update(float dt)
{
	for (auto& bullet : m_pBullets)
	{
		bullet->Update(dt);
	}

	for (auto it = m_pBullets.begin(); it != m_pBullets.end();)
	{
		if (!(*it)->IsActive())
		{
			Release(std::move(*it));
			it = m_pBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GunBoots::Draw()
{
	for (auto& bullet : m_pBullets)
	{
		bullet->Draw();
	}

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

	auto bullet = Acquire();
	if (!bullet) return false;

	//当たり判定用
	bullet->SetFloatingEnemy(m_FloatingEnemy);

	bullet->Initialize();
	bullet->SetPosition(position);
	m_pBullets.push_back(std::move(bullet));

	m_Ammo--;

	return true;
}
