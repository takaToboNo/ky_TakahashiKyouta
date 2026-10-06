#pragma once
#include "GameObject.h"

class GunBoots : public GameObject
{
private:
	static constexpr int kMaxAmmo = 10;
	int m_Ammo = 0;
	int m_ShotInterval = 0;

public:
	GunBoots() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
	void Destroy() override;

	bool CreateBullet();
	void Reload() { m_Ammo = kMaxAmmo; }
	int GetAmmo() { return m_Ammo; }
};
