#include <random>
#include <iostream>
#include "StageManager.h"
#include "DxLib.h"
#include "MathHelper.h"
#include "GameObject.h"
#include "GameObjectManager.h"

#include "SolidBlock.h"
#include "BreakableBlock.h"
#include "WalkerEnemy.h"
#include "FloatingEnemy.h"
#include "Player.h"
#include "Camera.h"

bool StageManager::Initialize(GameObjectManager& manager)
{
	if (!LoadMapsData()) return false;

	SetRandomNumbers();
	SetSections();

	m_StageObjectPools.solidBlockPool.Setup(manager, SOLID_BLOCK_POOL_SIZE);
	m_StageObjectPools.breakableBlockPool.Setup(manager, BREAKABLE_BLOCK_POOL_SIZE);
	m_StageObjectPools.walkerEnemyPool.Setup(manager, WALKER_ENEMY_POOL_SIZE);
	m_StageObjectPools.floatingEnemyPool.Setup(manager, FLOATING_ENEMY_POOL_SIZE);

	return true;
}

void StageManager::Finalize()
{
}

void StageManager::Update(GameObjectManager& manager, Player* player)
{
#ifdef _DEBUG
	m_ActiveSolidBlockCount = 0;
	m_ActiveBreakableBlockCount = 0;
	m_ActiveFloatingEnemyCount = 0;
	m_ActiveWalkerEnemyCount = 0;
	for (auto& solidobj : m_StageObjectPools.solidBlockPool.GetObjectPool())
	{
		if (solidobj->IsActive())
		{
			m_ActiveSolidBlockCount++;
		}
	}
	for (auto& solidobj : m_StageObjectPools.breakableBlockPool.GetObjectPool())
	{
		if (solidobj->IsActive())
		{
			m_ActiveBreakableBlockCount++;
		}
	}
	for (auto& solidobj : m_StageObjectPools.floatingEnemyPool.GetObjectPool())
	{
		if (solidobj->IsActive())
		{
			m_ActiveFloatingEnemyCount++;
		}
	}
	for (auto& solidobj : m_StageObjectPools.walkerEnemyPool.GetObjectPool())
	{
		if (solidobj->IsActive())
		{
			m_ActiveWalkerEnemyCount++;
		}
	}
#endif

	//プレイヤーの現在いる区間を探す
	int currentSection = FindCurrentSection(player->GetPosition().y);
	if (m_CurrentSection == currentSection) return;

	//プレイヤーの現在いる区間とその区間に隣接した区間のみ有効にする
	for (int i = 0; i < STAGE_SECTION_COUNT; i++)
	{
		bool isNeighbor = (std::abs(currentSection - i) <= 1);

		if (!m_Sections[i].map) return;

		if (!isNeighbor && m_Sections[i].isActive)
		{
			DeactivateSection(i);
		}

		if (isNeighbor && !m_Sections[i].isActive)
		{
			ActivateSection(i, player);
		}
	}

	//プレイヤーが全区間を通り抜けたら最初に戻す
	if (currentSection == STAGE_SECTION_COUNT)
	{
		m_StageLoopCount++;

		ResetStageObjectPools();

		SetRandomNumbers();
		SetSections();

		player->SetPosition({ WINDOW_WIDTH * 0.5f,WINDOW_HEIGHT * 0.5f });
		player->SetVelocity(Vector2::Zero());
		if (m_Camera)
		{
			m_Camera->SnapToTarget();
		}
	}

	m_CurrentSection = currentSection;
}

void StageManager::Draw()
{
#ifdef _DEBUG
	const int startPosX = 1000;
	const int startPosY = 30;
	DrawFormatString(startPosX, startPosY, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "CurrentSection : %d", m_CurrentSection);

	DrawFormatString(startPosX, startPosY + 60, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "ActiveSolidBlock : %d/%d", m_ActiveSolidBlockCount, SOLID_BLOCK_POOL_SIZE);
	DrawFormatString(startPosX, startPosY + 80, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "ActiveFloatingEnemy : %d/%d", m_ActiveFloatingEnemyCount, FLOATING_ENEMY_POOL_SIZE);
	DrawFormatString(startPosX, startPosY + 100, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "ActiveWalkerEnemy : %d/%d", m_ActiveWalkerEnemyCount, WALKER_ENEMY_POOL_SIZE);
	DrawFormatString(startPosX, startPosY + 120, GetColor(DEBUG_COUNT_COLOR.r, DEBUG_COUNT_COLOR.g, DEBUG_COUNT_COLOR.b), "ActiveBreakableBlock : %d/%d", m_ActiveBreakableBlockCount, BREAKABLE_BLOCK_POOL_SIZE);

	if (!m_Camera) return;

	for (int i = 0; i < STAGE_SECTION_COUNT; i++)
	{
		if (m_Sections[i].isActive)
		{
			Vector2 pos = m_Sections[i].startPosition;
			int x1, y1;
			x1 = static_cast<int>((pos.x - TILE_SIZE * 0.5f) - m_Camera->GetPosition().x);
			y1 = static_cast<int>((pos.y - TILE_SIZE * 0.5f) - m_Camera->GetPosition().y);
			int x2, y2;
			x2 = static_cast<int>(pos.x + (MAP_SIZE_X * TILE_SIZE) - m_Camera->GetPosition().x - TILE_SIZE * 0.5f);
			y2 = static_cast<int>(pos.y + (MAP_SIZE_Y * TILE_SIZE) - m_Camera->GetPosition().y - TILE_SIZE * 0.5f);

			DrawBox(x1, y1, x2, y2, GetColor(RED.r, RED.g, RED.b), FALSE);
		}
	}
#endif
}

void StageManager::SetRandomNumbers()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::array<int, MIDDLE_MAP_ALL> numbers{ 0,1,2,3,4,5,6,7,8,9 };
	std::shuffle(numbers.begin(), numbers.end(), gen);

	//重複なしで数値を取得
	//スタートとゴールを除いた中間区画数
	for (int i = 0; i < MIDDLE_SECTION_COUNT; i++)
	{
		m_Numbers[i] = numbers[i];
	}
}

void StageManager::SetSections()
{
	float sectionY = TILE_SIZE * static_cast<float>(MAP_SIZE_Y);

	for (int i = 0; i < STAGE_SECTION_COUNT; i++)
	{
		m_Sections[i].startPosition.x = STAGE_LEFT;
		m_Sections[i].gameObjects.clear();
		m_Sections[i].isActive = false;
	}

	//スタート
	m_Sections[0].map = &m_StartMap;
	m_Sections[0].startPosition.y = 0.0f;
	//ゴール
	m_Sections[STAGE_SECTION_COUNT - 1].map = &m_GoalMap;
	m_Sections[STAGE_SECTION_COUNT - 1].startPosition.y = sectionY * (STAGE_SECTION_COUNT - 1);

	//中間区画
	for (int i = 1; i < MIDDLE_SECTION_COUNT + 1; i++)
	{
		m_Sections[i].map = &m_MiddleMaps[m_Numbers[i - 1]];
		m_Sections[i].startPosition.y = sectionY * i;
	}
}

int StageManager::FindCurrentSection(float playerPositionY) const
{
	float sectionY = TILE_SIZE * static_cast<float>(MAP_SIZE_Y);

	for (int i = 0; i < STAGE_SECTION_COUNT; i++)
	{
		if (playerPositionY > m_Sections[i].startPosition.y && playerPositionY <= m_Sections[i].startPosition.y + sectionY)
		{
			return i;
		}
	}

	if (playerPositionY > m_Sections[STAGE_SECTION_COUNT - 1].startPosition.y + sectionY)
	{	//最後の区間より下にいる
		return STAGE_SECTION_COUNT;
	}

	return -1;
}

void StageManager::ActivateSection(int index, Player* player)
{
	const Vector2& pos = m_Sections[index].startPosition;

	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			Vector2 offset = { pos.x + j * TILE_SIZE,pos.y + i * TILE_SIZE };

			MapObjectType mapObjectType = static_cast<MapObjectType>(m_Sections[index].map->GetMapObjectType(i, j));
			switch (mapObjectType)
			{
			case MapObjectType::SolidBlock://壊れるブロック------------------------------------
			{
				SolidBlock* solidBlock = m_StageObjectPools.solidBlockPool.Get();
				if (solidBlock)
				{
					solidBlock->SetPosition(offset);
					solidBlock->Activate();
					m_Sections[index].gameObjects.push_back(solidBlock);
				}
				break;
			}
			case MapObjectType::BreakableBlock://壊れるブロック-------------------------------------------
			{
				BreakableBlock* breakableBlock = m_StageObjectPools.breakableBlockPool.Get();
				if (breakableBlock)
				{
					breakableBlock->SetPosition(offset);
					breakableBlock->Activate();
					m_Sections[index].gameObjects.push_back(breakableBlock);
				}
				break;
			}
			case MapObjectType::FloatingEnemy://浮遊敵-------------------------------------------------
			{
				FloatingEnemy* floatingEnemy = m_StageObjectPools.floatingEnemyPool.Get();
				if (floatingEnemy)
				{
					floatingEnemy->SetSpawnPosition(offset);
					floatingEnemy->Activate();
					floatingEnemy->SetPlayer(player);
					m_Sections[index].gameObjects.push_back(floatingEnemy);
				}
				break;
			}
			case MapObjectType::WalkerEnemy://歩行敵---------------------------------------------
			{
				WalkerEnemy* walkerEnemy = m_StageObjectPools.walkerEnemyPool.Get();
				if (walkerEnemy)
				{
					walkerEnemy->SetSpawnPosition(offset);
					walkerEnemy->Activate();
					m_Sections[index].gameObjects.push_back(walkerEnemy);
				}
				break;
			}
			default://なにもなし-----------------------------------------------------------------
				break;
			}
		}
	}
	m_Sections[index].isActive = true;
}

void StageManager::DeactivateSection(int index)
{
	for (GameObject* obj : m_Sections[index].gameObjects)
	{
		obj->Deactivate();
	}
	m_Sections[index].isActive = false;
	m_Sections[index].gameObjects.clear();
}

bool StageManager::LoadMapsData()
{
	bool result = true;

	result = m_StartMap.LoadMapData("Data/Map/start.csv");
	if (!result) return false;

	result = m_GoalMap.LoadMapData("Data/Map/goal.csv");
	if (!result) return false;

	for (int i = 0; i < MIDDLE_MAP_ALL; i++)
	{
		std::string fileName = "Data/Map/middle_" + std::to_string(i + 1) + ".csv";
		result = m_MiddleMaps[i].LoadMapData(fileName);
		if (!result) return false;
	}

	return true;
}

void StageManager::ResetStageObjectPools() const
{
	for (SolidBlock* obj : m_StageObjectPools.solidBlockPool.GetObjectPool())
	{
		obj->Deactivate();
	}
	for (BreakableBlock* obj : m_StageObjectPools.breakableBlockPool.GetObjectPool())
	{
		obj->Deactivate();
	}
	for (FloatingEnemy* obj : m_StageObjectPools.floatingEnemyPool.GetObjectPool())
	{
		obj->Deactivate();
	}
	for (WalkerEnemy* obj : m_StageObjectPools.walkerEnemyPool.GetObjectPool())
	{
		obj->Deactivate();
	}
}
