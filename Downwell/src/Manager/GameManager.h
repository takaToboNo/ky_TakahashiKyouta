#pragma once
#include "SceneManager.h"
#include "Timer.h"

class GameManager
{
private:
	Timer m_Timer;
	SceneManager m_SceneManager;
	bool m_IsRunning = true;

public:
	GameManager() = default;
	~GameManager() = default;

	bool Initialize();
	void Finalize();
	int Run();
};