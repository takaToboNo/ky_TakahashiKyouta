#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Bullet.h"

class GunBoots : public GameObject
{
private:
	static constexpr int kMaxAmmo = 10;
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
			return std::make_unique<Bullet>();
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
	void Update() override;
	void Draw() override;
	void Destroy() override;

	bool CreateBullet();
	void Reload() { m_Ammo = kMaxAmmo; }
	int GetAmmo() { return m_Ammo; }
};
