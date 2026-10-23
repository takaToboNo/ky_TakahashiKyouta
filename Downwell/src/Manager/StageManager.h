#pragma once
#include <array>
#include <vector>
#include "Vector2.h"
#include "GameHelper.h"
#include "Map.h"
#include "ObjectPool.h"

class GameObjectManager;
class GameObject;
class SolidBlock;
class BreakableBlock;
class WalkerEnemy;
class FloatingEnemy;
class Player;
class Camera;

struct StageObjectPools
{
	ObjectPool<SolidBlock>		solidBlockPool;
	ObjectPool<BreakableBlock>	breakableBlockPool;
	ObjectPool<WalkerEnemy>		walkerEnemyPool;
	ObjectPool<FloatingEnemy>	floatingEnemyPool;
};

struct Section
{
	Map* map = nullptr;
	Vector2 startPosition = Vector2::Zero();
	bool isActive = false;
	std::vector<GameObject*> gameObjects{};
};

class StageManager
{
private:
	static constexpr int SOLID_BLOCK_POOL_SIZE = 500;
	static constexpr int BREAKABLE_BLOCK_POOL_SIZE = 100;
	static constexpr int WALKER_ENEMY_POOL_SIZE = 30;
	static constexpr int FLOATING_ENEMY_POOL_SIZE = 30;

	StageObjectPools m_StageObjectPools;

	Map m_StartMap;
	Map m_GoalMap;

	std::array<Map, MIDDLE_MAP_ALL> m_MiddleMaps{};
	std::array<Section, STAGE_SECTION_COUNT> m_Sections{};
	std::array<int, MIDDLE_SECTION_COUNT> m_Numbers{};//ì«Ç›çûÇﬁcsvÉtÉ@ÉCÉãÇÃî‘çÜ

	int m_CurrentSection = -1;


	std::array<Map, STAGE_SECTION_COUNT> m_Maps{};

	int m_ActiveSolidBlockCount = 0;
	int m_ActiveBreakableBlockCount = 0;
	int m_ActiveFloatingEnemyCount = 0;
	int m_ActiveWalkerEnemyCount = 0;
	

public:
	StageManager() = default;
	~StageManager() = default;

	bool Initialize(GameObjectManager& manager);
	void Finalize();
	void Update(GameObjectManager& manager, Player* player);
	void Draw(Camera& camera);

	int GetCurrentSection() { return m_CurrentSection; }

private:
	void SetRandomNumbers();
	void SetSections();
	int FindCurrentSection(float playerPositionY);

	void ActivateSection(int index, Player* player);
	void DeactivateSection(int index);
};