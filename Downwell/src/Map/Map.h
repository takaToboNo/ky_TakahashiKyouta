#pragma once
#include <string>
#include "GameHelper.h"

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

	int GetMapObjectType(int y, int x) const { return m_Map[y][x]; }
};