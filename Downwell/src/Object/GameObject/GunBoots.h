#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Bullet.h"
#include "ObjectPool.h"

class GameObjectManager;
class Player;

class GunBoots : public Object
{
private:
	static constexpr int BULLET_POOL_SIZE = 20;
	static constexpr int MAX_AMMO = 10;
	int m_Ammo = 0;
	int m_ShotInterval = 0;

	ObjectPool<Bullet> m_BulletPool;

public:
	GunBoots() = default;

	void SetupBullet(GameObjectManager& manager);

	void Initialize() override;
	void Finalize() override;
	void Update(float dt) override;
	void Draw();
	void Destroy() override;

	bool CreateBullet(const Vector2& position);
	void Reload() { m_Ammo = MAX_AMMO; }
	int GetAmmo() { return m_Ammo; }
};
