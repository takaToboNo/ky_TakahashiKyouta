#pragma once
#include "SceneManager.h"
#include "Time.h"

class GameManager
{
private:
	Time m_Time;
	SceneManager m_SceneManager;
	bool m_IsRunning = true;

public:
	GameManager() = default;
	~GameManager() = default;

	bool Initialize();
	void Finalize();
	int Run();
};