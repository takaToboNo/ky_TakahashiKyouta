#pragma once

class Player;

class IPlayerState
{
public:
	IPlayerState() = default;
	virtual ~IPlayerState() = default;

	virtual void Enter(Player&) = 0;
	virtual void Update(Player&) = 0;
	virtual void Exit(Player&) = 0;
};