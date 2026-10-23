#pragma once
#include "UI.h"

class GunBoots;

class AmmoGauge : public UI
{
private:
	GunBoots* m_GunBoots = nullptr;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw() override;
	void Destroy() override;

	void SetGunBoots(GunBoots* gunBoots) { m_GunBoots = gunBoots; }

};