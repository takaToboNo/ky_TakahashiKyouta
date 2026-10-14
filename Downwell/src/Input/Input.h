#pragma once
#include <array>
#include <vector>
#include "DxLib.h"

enum class Action
{
	Up = 0,
	Down,
	Right,
	Left,
	Action,
	Decide,
	End,
	Max
};

class Input
{
private:
	static constexpr int MAX_KEY = 256;

	static char m_NowKey[MAX_KEY];
	static char m_PreKey[MAX_KEY];

	static std::array<std::vector<int>, static_cast<int>(Action::Max)> m_KeyBindings;

public:
	Input() = delete;

	static void Update();

	static bool IsPress(Action action);
	static bool IsTrigger(Action action);
	static bool IsRelease(Action action);
};