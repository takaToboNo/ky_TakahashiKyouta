#pragma once
#include <string>
#include "Vector2.h"
#include "GameHelper.h"
#include <vector>

class GameObjectManager;
class Player;
class GameObject;

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
	int m_Map[MAP_SIZE_Y][MAP_SIZE_X]{};

public:
	Map() = default;
	~Map() = default;

	bool LoadMapData(const std::string& mapName);

	void GenerateMap(GameObjectManager& manager, const Vector2& startPosition, Player* player, std::vector<GameObject*>& gameObject);

};