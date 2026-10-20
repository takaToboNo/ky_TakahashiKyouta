#pragma once
#include <string>
#include "Vector2.h"
#include "GameHelper.h"

class GameObjectManager;
class Player;

enum class MapObjectType
{
	None = 0,
	SolidBlock,
	BreakableBlock,
	FloatingEnemy,
	WalkerEnemy,
};

class Map
{
private:
	int m_Map[MAP_SIZE_Y][MAP_SIZE_X];

public:
	Map() = default;
	~Map() = default;

	void LoadMapData(const std::string& mapName);

	//StageManager‚ÉˆÚ‚·
	void SetMap(GameObjectManager& manager, const Vector2& startPosition, Player* player);

};