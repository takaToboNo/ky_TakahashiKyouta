#pragma once
#include "UI.h"

class StageManager;

class StageCount : public UI
{
private:
	StageManager* m_StageManager = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void SetStageManager(StageManager* stageManager) { m_StageManager = stageManager; }

};