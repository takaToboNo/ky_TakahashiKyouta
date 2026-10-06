#pragma once

#include "Player.h"	//‰¼

class SceneManager
{
private:
	std::unique_ptr<Player> m_pPlayer = std::make_unique<Player>();

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};
