#pragma once
#include "UI.h"

class Player;

class LifeGauge : public UI
{
private:
	Player* m_Player = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void SetPlayer(Player* player) { m_Player = player; }

};