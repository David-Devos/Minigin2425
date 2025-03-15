#pragma once
#include "Command.h"
//#include "GameObject.h"
namespace dae
{
	class GameObject;
}

class GameActorCommand : public Command
{
protected:
	dae::GameObject* m_pActor;
	dae::GameObject* GetActor() const { return m_pActor; }
public:
	GameActorCommand(dae::GameObject* actor);
	virtual ~GameActorCommand();
	virtual void Execute() = 0;
	//virtual void Undo() = 0;
};

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
private:
	int m_MoveRight;
	int m_MoveDown;
};

class PelletEatCommand final : public GameActorCommand
{
public:
	PelletEatCommand(dae::GameObject* actor);
	void Execute() override;
private:
	int m_MoveRight;
	int m_MoveDown;
};