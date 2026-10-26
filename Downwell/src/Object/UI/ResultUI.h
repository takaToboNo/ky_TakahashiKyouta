#pragma once
#include "UI.h"

class Player;
class StageManager;

class ResultUI : public UI
{
private:
	Player* m_Player = nullptr;
	StageManager* m_StageManager = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void SetPlayer(Player* player) { m_Player = player; }
	void SetStageManager(StageManager* manager) { m_StageManager = manager; }

};