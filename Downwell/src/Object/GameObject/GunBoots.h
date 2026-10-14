#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Bullet.h"

class GunBoots : public Object
{
private:
	static constexpr int MAX_POOL_SIZE = 20;
	static constexpr int MAX_AMMO = 10;
	int m_Ammo = 0;
	int m_ShotInterval = 0;

	std::vector<std::unique_ptr<Bullet>> m_BulletPool;
	std::vector<std::unique_ptr<Bullet>> m_pBullets;

public:
	GunBoots() = default;

	std::unique_ptr<Bullet> Acquire()
	{
		if (m_BulletPool.empty())
		{
			return nullptr;
		}
		else
		{
			auto bullet = std::move(m_BulletPool.back());
			m_BulletPool.pop_back();
			return bullet;
		}
	}

	void Release(std::unique_ptr<Bullet> bullet)
	{
		m_BulletPool.push_back(std::move(bullet));
	}


	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	bool CreateBullet(const Vector2& position);
	void Reload() { m_Ammo = MAX_AMMO; }
	int GetAmmo() { return m_Ammo; }
};
