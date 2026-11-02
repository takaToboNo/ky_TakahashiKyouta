#pragma once

class ImGuiManager
{
private:


public:
	ImGuiManager() = default;
	~ImGuiManager() = default;

	void Initialize();
	void Finalize();
	void BeginFrame();
	void EndFrame();

};