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

bool Map::LoadMapData(const std::string& mapName)
{
	int fileHandle = FileRead_open((mapName).c_str());
	if (fileHandle == 0) return false;

	int result;

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		char line[256];
		result = FileRead_gets(line, sizeof(line), fileHandle);
		if (result == -1) return false;

		std::stringstream ss(line);
		std::string cell;

		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			std::getline(ss, cell, ',');
			m_Map[y][x] = static_cast<int>(std::stoi(cell));
		}
	}

	result = FileRead_close(fileHandle);
	if (result == -1) return false;

	return true;
}

void Map::GenerateMap(GameObjectManager& manager, const Vector2& startPosition, Player* player)
{
	const Vector2& pos = startPosition;

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			Vector2 offset = { pos.x + j * TILE_SIZE,pos.y + i * TILE_SIZE };

			MapObjectType mapObjectType = static_cast<MapObjectType>(m_Map[i][j]);
			switch (mapObjectType)
			{
			case MapObjectType::SolidBlock://壊れるブロック------------------------------------
			{
				SolidBlock* solidBlock = manager.AddGameObject(std::make_unique<SolidBlock>());
				if (solidBlock)
				{
					solidBlock->SetPosition(offset);
					solidBlock->SetActive(true);
				}
				break;
			}
			case MapObjectType::BreakableBlock://壊れるブロック-------------------------------------------
			{
				BreakableBlock* breakableBlock = manager.AddGameObject(std::make_unique<BreakableBlock>());
				if (breakableBlock)
				{
					breakableBlock->SetPosition(offset);
					breakableBlock->SetActive(true);
				}
				break;
			}
			case MapObjectType::FloatingEnemy://浮遊敵-------------------------------------------------
			{
				FloatingEnemy* floatingEnemy = manager.AddGameObject(std::make_unique<FloatingEnemy>());
				if (floatingEnemy)
				{
					floatingEnemy->SetPosition(offset);
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
					walkerEnemy->SetPosition(offset);
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
