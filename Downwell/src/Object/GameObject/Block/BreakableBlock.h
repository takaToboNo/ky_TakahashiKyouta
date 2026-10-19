#pragma once
#include "Block.h"

class Camera;

class BreakableBlock : public Block
{
private:

public:
	BreakableBlock() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw(const Camera& camera) override;
	void Destroy() override;

	void OnCollision(GameObject* other, const HitInfo& hitInfo) override;
};