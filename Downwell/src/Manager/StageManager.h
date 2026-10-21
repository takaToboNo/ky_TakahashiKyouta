#pragma once
#include <array>
#include "GameHelper.h"
#include "Map.h"

struct Section
{
	Map* map = nullptr;
	float offsetY = 0.0f;
};

class StageManager
{
private:
	Map m_StartMap;
	Map m_GoalMap;

	std::array<Map, MIDDLE_MAP_ALL> m_MiddleMaps{};
	std::array<Section, STAGE_SECTION_COUNT> m_Sections{};
	std::array<int, MIDDLE_SECTION_COUNT> m_Numbers{};//“Ç‚İ‚Şcsvƒtƒ@ƒCƒ‹‚Ì”Ô†

	int m_CurrentSection = -1;


	std::array<Map, STAGE_SECTION_COUNT> m_Maps{};
	

public:
	StageManager() = default;
	~StageManager() = default;

	bool Initialize();
	void Finalize();
	void Update(float playerPositionY);
	void Draw();

	void GenerateStage(GameObjectManager& manager, const Vector2& startPosition, Player* player);

	int GetCurrentSection() { return m_CurrentSection; }

private:
	void SetRandomNumbers();
	void SetSections();
	int FindCurrentSection(float playerPositionY);
};