#pragma once
#include "SceneManager.h"

class GameManager
{
private:
	SceneManager m_SceneManager;
	bool m_IsRunning = true;

public:
	GameManager() = default;
	~GameManager() = default;

	void Initialize();
	void Finalize();
	void Run();
};