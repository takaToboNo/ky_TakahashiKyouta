#include "Map.h"
#include "GameObjectManager.h"

#include "DxLib.h"
#include <sstream>

#include "SolidBlock.h"
#include "BreakableBlock.h"
#include "FloatingEnemy.h"
#include "WalkerEnemy.h"
#include "Player.h"
#include "GameHelper.h"
#include <cassert>

void Map::LoadMapData(const std::string& mapName)
{
	int fileHandle = FileRead_open(("Data/Map/" + mapName).c_str());
	assert(fileHandle != 0);

	int result;

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		char line[256];
		result = FileRead_gets(line, sizeof(line), fileHandle);
		assert(result != -1);

		std::stringstream ss(line);
		std::string cell;

		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			std::getline(ss, cell, ',');
			m_Map[y][x] = static_cast<int>(std::stoi(cell));
		}
	}

	result = FileRead_close(fileHandle);
	assert(result != -1);

	return;
}

void Map::SetMap(GameObjectManager& manager, const Vector2& startPosition, Player* player)
{
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			MapObjectType mapObjectType = static_cast<MapObjectType>(m_Map[i][j]);
			switch (mapObjectType)
			{
			case MapObjectType::SolidBlock://壊れるブロック------------------------------------
			{
				SolidBlock* solidBlock = manager.AddGameObject(std::make_unique<SolidBlock>());
				if (solidBlock)
				{
					solidBlock->SetPosition({ startPosition.x + j * TILE_SIZE,startPosition.y + i * TILE_SIZE });
					solidBlock->SetActive(true);
				}
				break;
			}
			case MapObjectType::BreakableBlock://壊れるブロック-------------------------------------------
			{
				BreakableBlock* breakableBlock = manager.AddGameObject(std::make_unique<BreakableBlock>());
				if (breakableBlock)
				{
					breakableBlock->SetPosition({ startPosition.x + j * TILE_SIZE,startPosition.y + i * TILE_SIZE });
					breakableBlock->SetActive(true);
				}
				break;
			}
			case MapObjectType::FloatingEnemy://浮遊敵-------------------------------------------------
			{
				FloatingEnemy* floatingEnemy = manager.AddGameObject(std::make_unique<FloatingEnemy>());
				if (floatingEnemy)
				{
					floatingEnemy->SetPosition({ startPosition.x + j * TILE_SIZE,startPosition.y + i * TILE_SIZE });
					floatingEnemy->SetActive(true);
					floatingEnemy->SetPlayer(player);
				}
				break;
			}
			case MapObjectType::WalkerEnemy://歩行敵---------------------------------------------
			{
				WalkerEnemy* walkerEnemy = manager.AddGameObject(std::make_unique<WalkerEnemy>());
				if (walkerEnemy)
				{
					walkerEnemy->SetPosition({ startPosition.x + j * TILE_SIZE,startPosition.y + i * TILE_SIZE });
					walkerEnemy->SetActive(true);
				}
				break;
			}
			default://なにもなし-----------------------------------------------------------------
				break;
			}
		}
	}
}
