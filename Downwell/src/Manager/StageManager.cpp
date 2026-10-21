#include <random>
#include <iostream>
#include "StageManager.h"
#include "DxLib.h"
#include "MathHelper.h"
#include "GameObject.h"

bool StageManager::Initialize()
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

    SetRandomNumbers();
    SetSections();

    return true;
}

void StageManager::Finalize()
{
}

void StageManager::Update(float playerPositionY)
{
    int currentSection = FindCurrentSection(playerPositionY);
    if (m_CurrentSection == currentSection) return;

    for (int i = 0; i < STAGE_SECTION_COUNT; i++)
    {
        bool isNeighbor = (std::abs(currentSection - i) <= 1);
        
        if (isNeighbor && !m_Sections[i].isActive)
        {
            for (auto* obj : m_Sections[i].gameObjects)
            {
                obj->SetActive(true);
            }
            m_Sections[i].isActive = true;
        }

        if (!isNeighbor && m_Sections[i].isActive)
        {
            for (auto* obj : m_Sections[i].gameObjects)
            {
                obj->SetActive(false);
            }
            m_Sections[i].isActive = false;
        }
    }

    m_CurrentSection = currentSection;
}

void StageManager::Draw()
{
#ifdef _DEBUG
    DrawFormatString(1000, 10, GetColor(RED.r, RED.g, RED.b), "CurrentSection : %d", m_CurrentSection);
#endif
}

void StageManager::GenerateStage(GameObjectManager& manager, const Vector2& startPosition, Player* player)
{
    for (int i = 0; i < STAGE_SECTION_COUNT; i++)
    {
        Vector2 offset = { startPosition.x, startPosition.y + m_Sections[i].offsetY };

        if (!m_Sections[i].map) return;

        m_Sections[i].map->GenerateMap(manager, offset, player, m_Sections[i].gameObjects);
    }
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

    //スタート
    m_Sections[0].map = &m_StartMap;
    m_Sections[0].offsetY = 0.0f;
    //ゴール
    m_Sections[STAGE_SECTION_COUNT - 1].map = &m_GoalMap;
    m_Sections[STAGE_SECTION_COUNT - 1].offsetY = sectionY * (STAGE_SECTION_COUNT - 1);

    //中間区画
    for (int i = 1; i < MIDDLE_SECTION_COUNT + 1; i++)
    {
        m_Sections[i].map = &m_MiddleMaps[m_Numbers[i - 1]];
        m_Sections[i].offsetY = sectionY * i;
    }
}

int StageManager::FindCurrentSection(float playerPositionY)
{
    float sectionY = TILE_SIZE * static_cast<float>(MAP_SIZE_Y);

    for (int i = 0; i < STAGE_SECTION_COUNT; i++)
    {
        if (playerPositionY > m_Sections[i].offsetY && playerPositionY <= m_Sections[i].offsetY + sectionY)
        {
            return i;
        }
    }

    return -1;
}
