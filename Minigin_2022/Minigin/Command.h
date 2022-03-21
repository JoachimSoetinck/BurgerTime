#pragma once
#include <iostream>

#include "GameObject.h"

class Command
{
public:
	Command( dae::GameObject* actor) { m_pTarget = actor; }
	virtual ~Command() = default;
	virtual void Execute() = 0;

private:
	dae::GameObject*  m_pTarget;
};

class FireCommand : public Command
{
public:
	FireCommand(dae::GameObject* actor);
	virtual void Execute( ) override { std::cout << "Fire" << std::endl; };
};

class DuckCommand : public Command
{
public:
	DuckCommand(dae::GameObject* actor);
	virtual void Execute( ) override { std::cout << "Duck" << std::endl; };
};

class JumpCommand : public Command
{
public:
	JumpCommand(dae::GameObject* actor);
	virtual void Execute( ) override { std::cout << "Jump" << std::endl; };
};

class FartCommand : public Command
{
public:
	FartCommand(dae::GameObject* actor);
	virtual void Execute( ) override { std::cout << "Fart" << std::endl; };
};

class LoseLive : public Command
{
public:
	virtual void Execute( ) override {
		
	};
};

