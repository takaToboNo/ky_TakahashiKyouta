#pragma once

#include "Player.h"	//‰¼
#include "GunBoots.h"	//‰¼
#include "Bullet.h"	//‰¼

class SceneManager
{
private:
	std::unique_ptr<Player> m_pPlayer = std::make_unique<Player>();
	std::unique_ptr<GunBoots> m_pGunBoots = std::make_unique<GunBoots>();
	std::unique_ptr<Bullet> m_pBullet = std::make_unique<Bullet>();

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};
