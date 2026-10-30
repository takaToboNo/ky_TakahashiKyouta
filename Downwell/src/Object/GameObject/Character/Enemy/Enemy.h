#pragma once
#include "Character.h"

class Enemy : public Character
{
protected:


public:
	Enemy() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;
};