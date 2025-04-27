#pragma once
#include "GameActorCommand.h"

class MoveCommand final : public GameActorCommand
{
public:
	MoveCommand(dae::GameObject* actor, int moveRight, int moveDown);
	void Execute() override;
private:
	int m_MoveRight;
	int m_MoveDown;
};

class DamageCommand final : public GameActorCommand
{
public:
	DamageCommand(dae::GameObject* actor);
	void Execute() override;
};

class PelletEatCommand final : public GameActorCommand
{
public:
	PelletEatCommand(dae::GameObject* actor);
	void Execute() override;
};
//temporary command for testing
class TempSoundCommand final : public GameActorCommand
{
public:
	TempSoundCommand(dae::GameObject* actor);
	void Execute() override;
};