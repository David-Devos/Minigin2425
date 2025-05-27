#pragma once
#include <glm.hpp>
#include "GameActorCommand.h"

class MoveCommand final : public GameActorCommand
{
public:
	MoveCommand(dae::GameObject* actor, glm::vec2 moveDir);
	void Execute() override;
private:
	glm::vec2 m_MoveDir;
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