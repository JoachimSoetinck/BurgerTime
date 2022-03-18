#pragma once
#include <iostream>
class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class FireCommand : public Command
{
	virtual void Execute() override { std::cout << "Fire" << std::endl; };
};

class DuckCommand : public Command
{
	virtual void Execute() override { std::cout << "Duck" << std::endl; };
};

class JumpCommand : public Command
{
	virtual void Execute() override { std::cout << "Jump" << std::endl; };
};

class FartCommand : public Command
{
	virtual void Execute() override { std::cout << "Fart" << std::endl; };
};

