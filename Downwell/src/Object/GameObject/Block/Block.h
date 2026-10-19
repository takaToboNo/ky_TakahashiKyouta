#pragma once
#include "GameObject.h"

class Block : public GameObject
{
protected:
	static constexpr float BLOCK_SIZE = 47.0f;

public:
	Block() = default;

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;
};