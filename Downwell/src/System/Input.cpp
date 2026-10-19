#include "input.h"

char Input::m_NowKey[Input::MAX_KEY] = {};
char Input::m_PreKey[Input::MAX_KEY] = {};

std::array<std::vector<int>, static_cast<int>(Action::Max)> Input::m_KeyBindings
{
	std::vector<int>{ KEY_INPUT_W, KEY_INPUT_UP },							// Up
	std::vector<int>{ KEY_INPUT_S, KEY_INPUT_DOWN },						// Down
	std::vector<int>{ KEY_INPUT_D, KEY_INPUT_RIGHT },						// Right
	std::vector<int>{ KEY_INPUT_A, KEY_INPUT_LEFT },						// Left
	std::vector<int>{ KEY_INPUT_LSHIFT, KEY_INPUT_RSHIFT, KEY_INPUT_SPACE },// Action(Jump,Shot)
	std::vector<int>{ KEY_INPUT_RETURN },									// Decide
	std::vector<int>{ KEY_INPUT_ESCAPE },									// End
};

void Input::Update()
{
	memcpy(m_PreKey, m_NowKey, sizeof(m_NowKey));
	GetHitKeyStateAll(m_NowKey);
}

bool Input::IsPress(Action action)
{
	const std::vector<int>& keys = m_KeyBindings[static_cast<int>(action)];

	for (int key : keys)
	{
		if (m_NowKey[key])
		{
			return true;
		}
	}

	return false;
}

bool Input::IsTrigger(Action action)
{
	const std::vector<int>& keys = m_KeyBindings[static_cast<int>(action)];

	for (int key : keys)
	{
		if (m_NowKey[key] && !m_PreKey[key])
		{
			return true;
		}
	}

	return false;
}

bool Input::IsRelease(Action action)
{
	const std::vector<int>& keys = m_KeyBindings[static_cast<int>(action)];

	for (int key : keys)
	{
		if (!m_NowKey[key] && m_PreKey[key])
		{
			return true;
		}
	}

	return false;
}