#pragma once
#include "UI.h"
#include "GameHelper.h"

class StageManager;

class StageCount : public UI
{
private:
	static constexpr float POSITION_X = STAGE_LEFT - 330.0f;
	static constexpr float POSITION_Y = 70.0f;

	StageManager* m_StageManager = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void Destroy() override;

	void SetStageManager(StageManager* stageManager) { m_StageManager = stageManager; }

};