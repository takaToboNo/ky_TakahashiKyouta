#pragma once

#include "Player.h"	//‰¼

class SceneManager
{
private:
	Player* m_pPlayer;//‰¼

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

};
