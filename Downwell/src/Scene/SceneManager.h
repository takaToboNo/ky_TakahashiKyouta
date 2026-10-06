#pragma once

#include "Player.h"	//‰¼
#include "GunBoots.h"	//‰¼

class SceneManager
{
private:
	std::unique_ptr<Player> m_pPlayer = std::make_unique<Player>();
	std::unique_ptr<GunBoots> m_pGunBoots = std::make_unique<GunBoots>();

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};
