#pragma once
#include "GameObject.h"

class Block : public GameObject
{
protected:

public:
	Block() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;
};