#pragma once
#include "SceneManager.h"
#include "Timer.h"
#include "ImGuiManager.h"

class GameManager
{
private:
	Timer m_Timer;
	SceneManager m_SceneManager;
	ImGuiManager m_ImGuiManager;
	bool m_IsRunning = true;

public:
	GameManager() = default;
	~GameManager() = default;

	bool Initialize();
	void Finalize();
	int Run();
};