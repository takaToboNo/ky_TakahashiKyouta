#pragma once
#include <memory>
#include "Scene.h"

#include "Player.h"	//‰¼
#include "GunBoots.h"	//‰¼
#include "WalkerEnemy.h"	//‰¼
#include "FloatingEnemy.h"	//‰¼

class GameScene : public Scene
{
private:
	std::unique_ptr<Player> m_pPlayer = std::make_unique<Player>();
	std::unique_ptr<GunBoots> m_pGunBoots = std::make_unique<GunBoots>();
	std::unique_ptr<WalkerEnemy> m_pWalkerEnemy = std::make_unique<WalkerEnemy>();
	std::unique_ptr<FloatingEnemy> m_pFloatingEnemy = std::make_unique<FloatingEnemy>();

public:
	GameScene() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};
