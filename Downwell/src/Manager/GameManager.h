#pragma once
#include "SceneManager.h"
#include "Timer.h"
#include "ImGuiManager.h"
#include "Renderer.h"

class GameManager
{
private:
	Timer m_Timer;
	Renderer m_Renderer;
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